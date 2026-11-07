/*
 * File    : InputValidator.cpp
 * Purpose : Implements validation functions (shared by 4 members)
 */
#include <string>
#include "InputValidator.h"

 // ===== Member 1: validateSixDigitInput =====
bool InputValidator::validateSixDigitInput(const std::string& input)
{
    // TODO (Member 1)
    return false;
}

// ===== Member 2: validateEncodedData =====
/* Checks that an encoded barcode string is valid before we draw it.
 * Input    : encoded -> string made of '1' (black bar) and '0' (white space)
 * Returns  : true if valid, false if invalid
 */
bool InputValidator::validateEncodedData(const std::string& encoded)
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
    bool validStart = (encoded.compare(0, 11, START_A) == 0) ||
        (encoded.compare(0, 11, START_B) == 0) ||
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
bool InputValidator::validateBMPHeader(const unsigned char header[], int size)
{
    // TODO (Member 3)
    return false;
}



// ===== Member 4: validateScannedPattern =====
bool InputValidator::validateScannedPattern(const std::string& pattern)
{
    // TODO (Member 4)
    return false;
}