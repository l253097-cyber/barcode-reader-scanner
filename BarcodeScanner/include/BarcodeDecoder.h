/*
 * File    : BarcodeDecoder.h
 * Purpose : Decodes scanned patterns back into digits (Members 4 and 5)
 */
#ifndef BARCODE_DECODER_H
#define BARCODE_DECODER_H

#include <string>

class BarcodeDecoder
{
public:
    // Member 4: one digit pattern -> digit char ('?' if unknown)
    static char decodeDigitPattern(const std::string& pattern);

    // Member 4: verifies decoded result (6 digits, structure, checksum)
    static bool verifyDecodedResult(const std::string& decoded);

    // Member 5: full scanned pattern -> original 6-digit string ("" on failure)
    static std::string decodeScannedPattern(const std::string& fullPattern);
};

#endif