/*
 * File    : InputValidator.cpp
 * Purpose : Implements validation functions (shared by 4 members)
 */
#include "InputValidator.h"

 //BMP stores numbers in little-endian order (lowest byte first),
 //so these helpers rebuild a number from its bytes.
static int le16(const unsigned char* p)
{
    return (int)(p[0] | (p[1] << 8));
}

static int le32(const unsigned char* p)
{
    return (int)((unsigned int)p[0] | ((unsigned int)p[1] << 8) | ((unsigned int)p[2] << 16) | ((unsigned int)p[3] << 24));
}

 // ===== Member 1: validateSixDigitInput =====
bool InputValidator::validateSixDigitInput(const std::string& input)
{
    // TODO (Member 1)
    return false;
}



// ===== Member 2: validateEncodedData =====
bool InputValidator::validateEncodedData(const std::string& encoded)
{
    // TODO (Member 2)
    return false;
}



// ===== Member 3: validateBMPHeader =====
bool InputValidator::validateBMPHeader(const unsigned char header[], int size)
{
    //The standard header is 54 bytes (14 file header + 40 info header)
    if (header == nullptr || size < 54) 
        return false;
    if (header[0] != 'B' || header[1] != 'M') 
        return false;

    //Field positions follow the BMP file format
    int pixelOffset = le32(header + 10);
    int dibSize = le32(header + 14);
    int width = le32(header + 18);
    int height = le32(header + 22);
    int planes = le16(header + 26);
    int bitDepth = le16(header + 28);
    int compression = le32(header + 30);

    if (dibSize < 40) return false;
    if (planes != 1) return false;
    if (bitDepth != 24) return false;      //only 24-bit images are supported
    if (compression != 0) return false;    //0 = uncompressed
    if (width <= 0 || width > MAX_WIDTH) return false;

    //A negative height means a top-down image; we only accept bottom-up
    //so the pixel reader can always assume the same row order.
    if (height <= 0) return false;

    if (pixelOffset < 54) return false;
    return true;
}



// ===== Member 4: validateScannedPattern =====
bool InputValidator::validateScannedPattern(const std::string& pattern)
{
    // TODO (Member 4)
    return false;
}