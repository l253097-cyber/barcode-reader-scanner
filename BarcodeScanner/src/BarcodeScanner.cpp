/*
 * File    : BarcodeScanner.cpp
 * Purpose : Row scanning and bar width detection (Member 3)
 */
#include "BarcodeScanner.h"

bool BarcodeScanner::scanPixelRow(const int matrix[][MAX_WIDTH], int width, int height, int row, char outPixels[])
{
    if (matrix == nullptr || outPixels == nullptr) return false;
    if (width <= 0 || width > MAX_WIDTH) return false;
    if (height <= 0) return false;
    if (row < 0 || row >= height) return false;   //row must exist in the image

    // Matrix convention: 1 = black, 0 = white
    for (int x = 0; x < width; x++)
        outPixels[x] = (matrix[row][x] == 1) ? '1' : '0';
    outPixels[width] = '\0';   // end the string
    return true;
}

int BarcodeScanner::detectBarWidths(const char rowPixels[], int widths[], int maxRuns)
{
    // TODO (Member 3)
    return 0;
}