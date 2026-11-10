/*
 * File    : BMPFileHandler.cpp
 * Purpose : Manual BMP reading/writing (shared by Members 1, 2, 3, 4)
 */
#include "BMPFileHandler.h"

 // ===== Member 1: writeBMPHeader =====
//Helper functions
//for planes and width depth we are using 16 bits
static void writeUInt16(std::ofstream& file, unsigned int v) {
    file.put((char)(v & 0xFF));
    file.put((char)((v >> 8) & 0xFF));
}

static void writeUInt32(std::ofstream& file, unsigned int v) {
    //put helps in moving one byte in file
	//we are writing 4 bytes of the integer in little endian format
	//we are right shifting the integer by 8,16,24 bits to get the next byte and writing it in file
	//We prepared mask of 0xFF to get the last 8 bits of the integer
    file.put((char)(v & 0xFF));
    file.put((char)((v >> 8) & 0xFF));
    file.put((char)((v >> 16) & 0xFF));
    file.put((char)((v >> 24) & 0xFF));
}
bool BMPFileHandler::writeBMPHeader(std::ofstream& file, int width, int height)
{
    if (width <= 0 || height <= 0 || width > MAX_WIDTH || height > MAX_HEIGHT || !file)
    {
        return false;
    }
    int rowSize = ((width * 3 + 3) / 4) * 4;
	int imageSize = rowSize * height;
    int fileSize = BMP_HEADER_SIZE + imageSize;
    //File Header->file information
	//every bmp file starts with BM in the first 2 bytes
    file.put('B');
    file.put('M');
    writeUInt32(file, fileSize);
    writeUInt32(file, 0);
    //Pixels Offset
    writeUInt32(file, BMP_HEADER_SIZE);
	//Info Header->image information
	writeUInt32(file, 40);    //passed header size
	writeUInt32(file, width); //width->pixels of image
	writeUInt32(file, height); //height->pixels of image
	writeUInt16(file, 1); //colour planes
	writeUInt16(file, 24); //bit depth(24 bits per pixel i.e 3 bytes B,G,R)
	writeUInt32(file, 0); //compression=none
	writeUInt32(file, imageSize); //bytes of pixel data
	writeUInt32(file, 2835); //horizontal resolution(~72 DPI)
	writeUInt32(file, 2835); //vertical resolution(~72 DPI)
	writeUInt32(file, 0); //colours in palette(none)
	writeUInt32(file, 0); //important colours(none)
	//this all above takes 40 bytes that's why header size is 40 bytes

    
    return true;
}



// ===== Member 2: writeBMPPixelData =====
bool BMPFileHandler::writeBMPPixelData(std::ofstream& file,
    const int matrix[][MAX_WIDTH], int width, int height)
{
    // TODO (Member 2)
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