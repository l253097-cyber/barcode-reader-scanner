/*
 * File    : BMPFileHandler.h
 * Purpose : Reads and writes 24-bit BMP files manually (Members 1, 2, 3, 4)
 */
#ifndef BMP_FILE_HANDLER_H
#define BMP_FILE_HANDLER_H

#include <fstream>
#include "Config.h"

class BMPFileHandler
{
public:
    // Member 1: writes the 54-byte BMP header
    static bool writeBMPHeader(std::ofstream& file, int width, int height);

    // Member 2: writes pixel matrix (BGR order + row padding)
    static bool writeBMPPixelData(std::ofstream& file,
        const int matrix[][MAX_WIDTH], int width, int height);

    // Member 3: reads header, returns values via reference parameters
    static bool readBMPHeader(std::ifstream& file,
        int& width, int& height, int& bitDepth, int& pixelOffset);

    // Member 4: reads pixel data into matrix (1 = black, 0 = white)
    static bool readBMPPixelData(std::ifstream& file,int matrix[][MAX_WIDTH], int width, int height, int pixelOffset);
};

#endif