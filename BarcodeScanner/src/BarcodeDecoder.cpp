/*
 * File    : BarcodeDecoder.cpp
 * Purpose : Pattern decoding and verification (Members 4 and 5)
 */
#include "BarcodeDecoder.h"
#include"BarcodeEncoder.h"

 // ===== Member 4: decodeDigitPattern =====
// instead of char i used int as return type
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
//structure test
bool BarcodeDecoder::verifyDecodedResult(const std::string& decoded)
{
    if (decoded.length() != 6)
        return false;
    for (int i = 0;i < decoded.length();i++)
    {
        if (decoded[i] < '0' || decoded[i]>'9')
            return false;
    }
    return decoded[0]!='0';
}
//helper
bool BarcodeDecoder::verifyDecodedResult(const std::string& decoded,int scannedChecksum)
{
    if (!verifyDecodedResult(decoded))
        return false;
    int p1 = (decoded[0] - '0') * 10 + (decoded[1] - '0');
    int p2 = (decoded[2] - '0') * 10 + (decoded[3] - '0');
    int p3 = (decoded[4] - '0') * 10 + (decoded[5] - '0');

    return scannedChecksum == BarcodeEncoder::calculateSum(p1, p2, p3);
}


// ===== Member 5: decodeScannedPattern =====
std::string BarcodeDecoder::decodeScannedPattern(const std::string& fullPattern)
{
    // TODO (Member 5)
    return "";
}