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
    outPixels[width] = '\0';   //end the string
    return true;
}

//Run-length encoding: "00110100" -> {2, 2, 1, 1, 2}
//The first run has the colour of the first pixel. Margins are not trimmed.
int BarcodeScanner::detectBarWidths(const char rowPixels[], int widths[], int maxRuns)
{
    if (rowPixels == nullptr || widths == nullptr || maxRuns <= 0) return 0;
    if (rowPixels[0] == '\0') return 0;
    if (rowPixels[0] != '0' && rowPixels[0] != '1') return 0;

    int count = 0, run = 1;
    for (int i = 1; rowPixels[i] != '\0'; i++)
    {
        if (rowPixels[i] != '0' && rowPixels[i] != '1') return 0;

        if (rowPixels[i] == rowPixels[i - 1])
            run++;                          // same colour: current run grows
        else
        {
            if (count >= maxRuns) return 0; // widths[] would overflow
            widths[count++] = run;          // colour changed: save the run
            run = 1;
        }
    }
    if (count >= maxRuns) return 0;
    widths[count++] = run;                  // save the last run
    return count;
}

string BarcodeScanner::widthsToPattern(const char rowPixels[], const int widths[], int runCount)
{
    if (runCount < 3)
        return "";
    if (rowPixels[0] != '0')
        return "";      // must start with a white quiet zone

    int moduleWidth = widths[1];
    for (int i = 1; i < runCount - 1; i++)
        if (widths[i] < moduleWidth) 
            moduleWidth = widths[i];
    if (moduleWidth <= 0) 
        return "";

    string pattern;
    char colour = '1';                        // first run after the margin is black
    for (int i = 1; i < runCount - 1; i++)
    {
        int modules = widths[i] / moduleWidth;   // how many modules wide this bar is
        for (int k = 0; k < modules; k++)
            pattern += colour;                   // add one character per module
        colour = (colour == '1') ? '0' : '1';
    }
    return pattern;
}