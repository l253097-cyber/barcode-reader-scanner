/*
 * File    : InputValidator.cpp
 * Purpose : Implements validation functions (shared by 4 members)
 */

#include<iostream>
#include <string>
#include "InputValidator.h"
using namespace std;
//hepler functions -member1
bool InputValidator::isEmpty(const string& s) {
	return s.empty();
}
bool InputValidator::isNumeric(const string& s) {
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}
bool InputValidator::hasValidLength(const string& s) {
	return s.length() == 6;
}
// ===== Member 1: validateSixDigitInput =====
bool InputValidator::validateSixDigitInput(const string& s, string& errorMessage)
{
	errorMessage = "";
	if (isEmpty(s)) {
		errorMessage = "Input is empty. Please enter a 6-digit number.";
		return false;
	}
	if (!isNumeric(s)) {
		errorMessage = "Input must contain digits (0-9) only.";
		return false;
	}
	if (!hasValidLength(s)) {
		errorMessage = "Input must be exactly 6 digits (you entered "
			+ to_string(s.length()) + ").";
		return false;
	}
	if (s[0] == '0') {
		errorMessage = "The first digit must be non-zero.";
		return false;
	}
	return true;
}

// ===== Member 2: validateEncodedData =====
/* Checks that an encoded barcode string is valid before we draw it.
 * encoded -> string made of '1' (black bar) and '0' (white space)
 */

bool InputValidator::validateEncodedData(const string& encoded)
{
    if (encoded.empty())
    {
        return false;
    }
    int length = (int)encoded.length();
    if (length > MAX_ENCODED_LEN)
    {
        return false;
    }
    bool hasBlackBar = false;
    for (int i = 0; i < length; i++)
    {
        char c = encoded[i];
        if (c != '0' && c != '1')        //only 0 and 1 is allowed
        {
            return false;
        }
        if (c == '1')
        {
            hasBlackBar = true;
        }
    }    
    if (!hasBlackBar)
    {
        return false;
    }

    // Code 128 structure check
    // A Code 128 barcode = START symbol (11 modules) + data symbols (11 each) + STOP symbol (13 modules)
    const std::string START_A = "11010000100";   // Start Code A
    const std::string START_B = "11010010000";   // Start Code B
    const std::string START_C = "11010011100";   // Start Code C
    const std::string STOP = "1100011101011"; // Stop pattern (13 modules)

    // Smallest possible barcode = start (11) + checksum (11) + stop (13) = 35
    if (length < 35)
    {
        return false;
    }
    // Everything except the stop (13) must be whole symbols of 11 modules
    if ((length - 13) % 11 != 0)
    {
        return false;
    }
    // The first 11 characters must be one of the three start patterns
    bool validStart = (encoded.compare(0, 11, START_A) == 0) || (encoded.compare(0, 11, START_B) == 0) ||
         (encoded.compare(0, 11, START_C) == 0);
    if (!validStart)
    {
        return false;
    }
    // The last 13 characters must be exactly the stop pattern
    if (encoded.compare(length - 13, 13, STOP) != 0)
    {
        return false;
    }
    return true;
}


// ===== Member 3: validateBMPHeader =====
static int le16(const unsigned char* p)
{
    return (int)(p[0] | (p[1] << 8));
}

static int le32(const unsigned char* p)
{
    return (int)((unsigned int)p[0] | ((unsigned int)p[1] << 8) | ((unsigned int)p[2] << 16) | ((unsigned int)p[3] << 24));
}

bool InputValidator::validateBMPHeader(const unsigned char header[], int size)
{
    //The standard header is 54 bytes (14 file header + 40 info header)

    if (header == nullptr || size < 54)
        return false;
    if (header[0] != 'B' || header[1] != 'M')
        return false;
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

    if (pixelOffset < 54) 
        return false;

    return true;

}



// ===== Member 4: validateScannedPattern =====
bool InputValidator::validateScannedPattern(const std::string& pattern)
{
	if (pattern.empty())
		return false;
	if (pattern.length() != expected_length)
		return false;
	for (int i = 0;i < pattern.length();i++)
	{
		if (pattern[i] != '0' && pattern[i] != '1')
			return false;
	}
	return true;
}