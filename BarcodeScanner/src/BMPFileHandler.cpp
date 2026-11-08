/*
 * File    : BMPFileHandler.cpp
 * Purpose : Manual BMP reading/writing (shared by Members 1, 2, 3, 4)
 */
#include "BMPFileHandler.h"
#include "InputValidator.h"

 // ===== Member 1: writeBMPHeader =====
bool BMPFileHandler::writeBMPHeader(std::ofstream& file, int width, int height)
{
    // TODO (Member 1)
    return false;
}



// ===== Member 2: writeBMPPixelData =====
bool BMPFileHandler::writeBMPPixelData(std::ofstream& file,
    const int matrix[][MAX_WIDTH], int width, int height)
{
    // TODO (Member 2)
    return false;
}



// ===== Member 3: readBMPHeader =====
bool BMPFileHandler::readBMPHeader(std::ifstream& file, int& width, int& height, int& bitDepth, int& pixelOffset)
{
    if (!file.is_open()) return false;

    unsigned char header[54];
    file.clear();                            //reset any earlier error flags
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(header), 54);
    if (file.gcount() != 54) return false;   //file shorter than a header

    if (!InputValidator::validateBMPHeader(header, 54)) return false;

    //Outputs are set only after validation passes, so a bad file
    //never leaves half-filled values in the caller's variables.
    //Bytes are combined little-endian, same as in the validator.
    width = (int)((unsigned int)header[18] | ((unsigned int)header[19] << 8) |
        ((unsigned int)header[20] << 16) | ((unsigned int)header[21] << 24));

    height = (int)((unsigned int)header[22] | ((unsigned int)header[23] << 8) |
        ((unsigned int)header[24] << 16) | ((unsigned int)header[25] << 24));

    bitDepth = header[28] | (header[29] << 8);

    pixelOffset = (int)((unsigned int)header[10] | ((unsigned int)header[11] << 8) |
        ((unsigned int)header[12] << 16) | ((unsigned int)header[13] << 24));

    return true;
}



// ===== Member 4: readBMPPixelData =====
bool BMPFileHandler::readBMPPixelData(std::ifstream& file,
    int matrix[][MAX_WIDTH], int width, int height, int pixelOffset)
{
    // TODO (Member 4)
    return false;
}