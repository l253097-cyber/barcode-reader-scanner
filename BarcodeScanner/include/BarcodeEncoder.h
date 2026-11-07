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
    // encodes 6 digits into full barcode string (with start/stop)
    static const int START_C = 105;   // Start Code C symbol value
    static const int STOP = 106;
    // Member 1: pattern of one digit, "" if digit is invalid
    static std::string getDigitPattern(int value);
    static std::string widthsToModules(const std::string& widths);
    static std::string getWidthPattern(int value);
    static int calculateSum(int p1, int p2, int p3);
    static std::string encodeSixDigits(const std::string& sixDigits);
    static bool verifyPattern();
};
#endif