/*
 * File    : BMPFileHandler.cpp
 * Purpose : Manual BMP reading/writing (shared by Members 1, 2, 3, 4)
 */
#include "BMPFileHandler.h"

 // ===== Member 1: writeBMPHeader =====
bool BMPFileHandler::writeBMPHeader(std::ofstream& file, int width, int height)
{
    // TODO (Member 1)
    return false;
}


// ===== Member 2: writeBMPPixelData =====
/*
 * Writes the pixel matrix into the BMP file (after the header)
 * BMP rules we must follow (24-bit BMP):
 *   1.Each pixel = 3 bytes in order Blue, Green, Red
 *   2.Each row must be a multiple of 4 bytes -> add padding bytes (0)
 *   3.Rows are stored BOTTOM to TOP (last row of the image comes first)
 */
bool BMPFileHandler::writeBMPPixelData(std::ofstream& file, const int matrix[][MAX_WIDTH], int width, int height)
{
    if (!file.is_open())
    {
        return false;
    }
    if (width < 1 || width > MAX_WIDTH || height < 1 || height > MAX_HEIGHT)
    {
        return false;
    }

    // calculate padding
    // one row has width * 3 bytes. Padding makes it a multiple of 4.
    // Eg: width 6 -> 18 bytes -> 18 % 4 = 2 -> padding = 2 bytes
    int rowBytes = width * 3;
    int padding = (4 - (rowBytes % 4)) % 4;

    return false;   
}



// ===== Member 3: readBMPHeader =====
bool BMPFileHandler::readBMPHeader(std::ifstream& file,
    int& width, int& height, int& bitDepth, int& pixelOffset)
{
    // TODO (Member 3)
    return false;
}



// ===== Member 4: readBMPPixelData =====
bool BMPFileHandler::readBMPPixelData(std::ifstream& file,
    int matrix[][MAX_WIDTH], int width, int height, int pixelOffset)
{
    // TODO (Member 4)
    return false;
}