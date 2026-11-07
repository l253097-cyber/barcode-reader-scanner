
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

bool BarcodeRenderer::renderBarcode(const std::string& encoded,
    int moduleWidth, int height, int quietZone,
    int matrix[][MAX_WIDTH], int& outWidth, int& outHeight)
{
    // TODO (Member 2)
    return false;
}