/*
 * File    : BarcodeDecoder.cpp
 * Purpose : Pattern decoding and verification (Members 4 and 5)
 */
#include "BarcodeDecoder.h"
#include"BarcodeEncoder.h"

 // ===== Member 4: decodeDigitPattern =====
int BarcodeDecoder::decodeDigitPattern(const std::string& pattern)
{
    if (pattern.length() != 11)
        return -1;
    for (int v = 0;v <= 102;v++)
    {
        if(BarcodeEncoder::getDigitPattern(v)==pattern)
            return v;
    }
    return -1;
}



// ===== Member 4: verifyDecodedResult =====
bool BarcodeDecoder::verifyDecodedResult(const std::string& decoded)
{
    // TODO (Member 4)
    return false;
}



// ===== Member 5: decodeScannedPattern =====
std::string BarcodeDecoder::decodeScannedPattern(const std::string& fullPattern)
{
    // TODO (Member 5)
    return "";
}