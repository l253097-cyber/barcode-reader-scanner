/*
 * File    : BMPFileHandler.cpp
 * Purpose : Manual BMP reading/writing (shared by Members 1, 2, 3, 4)
 */
#include "BMPFileHandler.h"
#include "InputValidator.h"

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

               // (+3 - maximum possible padding)
    unsigned char rowBuffer[MAX_WIDTH * 3 + 3];

    for (int row = height - 1; row >= 0; row--)
    {
        int pos = 0;  
        // convert each pixel of this row into 3 bytes
        for (int col = 0; col < width; col++)
        {
            unsigned char colour = 255;     // default white
            if (matrix[row][col] == 1)
            {
                colour = 0;                 // black pixel
            }

            rowBuffer[pos++] = colour;      // Blue
            rowBuffer[pos++] = colour;      // Green
            rowBuffer[pos++] = colour;      // Red
        }

        // add padding bytes at the end of the row
        for (int p = 0; p < padding; p++)
        {
            rowBuffer[pos++] = 0;
        }
        file.write((const char*)rowBuffer, pos);
        if (!file)
        {
            return false;
        }
    }
    return true;
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