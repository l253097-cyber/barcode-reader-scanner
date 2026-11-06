/*
 * File    : BarcodeEncoder.h
 * Purpose : Converts digits into barcode bar/space patterns (Member 1)
 */
#ifndef BARCODE_ENCODER_H
#define BARCODE_ENCODER_H

#include <string>

class BarcodeEncoder
{
public:
    // Member 1: pattern of one digit, "" if digit is invalid
    static std::string getDigitPattern(char digit);

    // Member 1: encodes 6 digits into full barcode string (with start/stop)
    static std::string encodeSixDigits(const std::string& sixDigits);
};

#endif