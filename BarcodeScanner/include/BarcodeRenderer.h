/*
 * File    : BarcodeRenderer.h
 * Purpose : Converts encoded barcode into a black/white pixel matrix (Member 2)
 */
#ifndef BARCODE_RENDERER_H
#define BARCODE_RENDERER_H

#include <string>
#include "Config.h"

class BarcodeRenderer
{
public:
    // Member 2: encoded string -> pixel matrix (no margins).
    // moduleWidth = pixels per single module, height = bar height in pixels.
    // Output: matrix filled, outWidth/outHeight set. Returns false on failure.
    static bool createPixelMatrix(const std::string& encoded,
        int moduleWidth, int height,
        int matrix[][MAX_WIDTH], int& outWidth, int& outHeight);

    // Member 2: final barcode image (adds white quiet zone left and right).
    static bool renderBarcode(const std::string& encoded,
        int moduleWidth, int height, int quietZone,
        int matrix[][MAX_WIDTH], int& outWidth, int& outHeight);
};

#endif