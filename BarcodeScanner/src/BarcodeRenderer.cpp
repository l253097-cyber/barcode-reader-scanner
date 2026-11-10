#include <string>
#include "BarcodeRenderer.h"
#include "InputValidator.h"

/*
  Turns the encoded string into a pixel matrix with NO margins
  Every character of the string is one "module".
  One module becomes moduleWidth pixels wide and every row of the image is the same (barcodes are vertical lines).
 * Input : encoded -> string of '0' and '1'
 *           moduleWidth -> pixels per module (e.g. 2)
 *          height -> number of rows in the image (e.g. 100)
 * Output: matrix, outWidth, outHeight
 * eg: "101", moduleWidth 2  ->  1 1 0 0 1 1   (width = 3 * 2 = 6)
 */
bool BarcodeRenderer::createPixelMatrix(const std::string& encoded, int moduleWidth, int height,
    int matrix[][MAX_WIDTH], int& outWidth, int& outHeight)
{
    outWidth = 0;
    outHeight = 0;
    if (!InputValidator::validateEncodedData(encoded))
    {
        return false;
    }
    // validate the size settings
    if (moduleWidth < 1)
    {
        return false;
    }
    if (height < 1 || height > MAX_HEIGHT)
    {
        return false;
    }
    // calculate the total width and check it fits in the array
    int length = (int)encoded.length();
    int totalWidth = length * moduleWidth;
    if (totalWidth > MAX_WIDTH)
    {
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        int pixelValue = 0;
        if (encoded[i] == '1')
        {
            pixelValue = 1;
        }
        // this module covers moduleWidth columns
        for (int k = 0; k < moduleWidth; k++)
        {
            int column = i * moduleWidth + k;   // exact column in the image
            // fill that column from top row to bottom row
            for (int row = 0; row < height; row++)
            {
                matrix[row][column] = pixelValue;
            }
        }
    }
    outWidth = totalWidth;
    outHeight = height;
    return true;
}

/*
  Builds the FINAL barcode image = barcode + white quiet zone on the left and right side
  (scanners need this white space to find where the barcode starts and ends)
 * Input : encoded -> string of '0' and '1'
 *         moduleWidth -> pixels per module (e.g. 2)
 *         height -> number of rows in the image (e.g. 100)
 *         quietZone -> white pixels on EACH side (Code 128 needs at least 10 modules, so use 10 * moduleWidth)
 * Output: matrix, outWidth, outHeight
 * layout: [ quietZone white ][ barcode bars ][ quietZone white ]
 */

bool BarcodeRenderer::renderBarcode(const std::string& encoded, int moduleWidth, int height, int quietZone,
    int matrix[][MAX_WIDTH], int& outWidth, int& outHeight)
{
    outWidth = 0;
    outHeight = 0;
    if (!InputValidator::validateEncodedData(encoded))
    {
        return false;
    }
    if (moduleWidth < 1 || quietZone < 0)
    {
        return false;
    }
    if (height < 1 || height > MAX_HEIGHT)
    {
        return false;
    }
    // total width = barcode + quiet zone on both sides, and it must fit in the array
    int length = (int)encoded.length();
    int barcodeWidth = length * moduleWidth;
    int totalWidth = barcodeWidth + 2 * quietZone;
    if (totalWidth > MAX_WIDTH)
    {
        return false;
    }

    // first paint the whole image white (0), this also makes the quiet zones
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < totalWidth; col++)
        {
            matrix[row][col] = 0;
        }
    }

    // draw only the black modules, shifted right by quietZone (the left margin)
    for (int i = 0; i < length; i++)
    {
        if (encoded[i] == '1')
        {
            for (int k = 0; k < moduleWidth; k++)
            {
                int column = quietZone + i * moduleWidth + k;
                // fill that column from top row to bottom row
                for (int row = 0; row < height; row++)
                {
                    matrix[row][column] = 1;
                }
            }
        }
    }
    outWidth = totalWidth;
    outHeight = height;
    return true;
}