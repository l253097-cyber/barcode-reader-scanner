/*
 * File    : BarcodeScanner.h
 * Purpose : Scans a pixel row and detects bar widths (Member 3)
 */
#ifndef BARCODE_SCANNER_H
#define BARCODE_SCANNER_H

#include "Config.h"

class BarcodeScanner
{
public:
    // Member 3: copies one row into outPixels as '0'/'1' chars + '\0'.
    // outPixels must have size >= MAX_WIDTH + 1. Returns false if row invalid.
    static bool scanPixelRow(const int matrix[][MAX_WIDTH],
        int width, int height, int row, char outPixels[]);

    // Member 3: run-lengths of bars/spaces. Fills widths[], returns count
    // (0 on failure). First run is always the first pixel's colour.
    static int detectBarWidths(const char rowPixels[], int widths[], int maxRuns);
};

#endif