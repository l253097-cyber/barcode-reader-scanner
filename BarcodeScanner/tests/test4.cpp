/*
 * File    : TestMember4.cpp
 * Purpose : Test cases for Member 4's functions
 */
#include <iostream>
#include "InputValidator.h"
#include "BarcodeDecoder.h"
#include "BarcodeEncoder.h"
#include "BMPFileHandler.h"

void runMember4Tests()
{
    std::cout << "\n--- Member 4 Tests ---\n";

    std::cout << InputValidator::validateScannedPattern(std::string(68, '1')) << " (expect 1)\n";
    std::cout << InputValidator::validateScannedPattern("1010") << " (expect 0)\n";
    std::cout << InputValidator::validateScannedPattern(std::string(68, '2')) << " (expect 0)\n";

    // decodeDigitPattern
    std::cout << BarcodeDecoder::decodeDigitPattern(BarcodeEncoder::getDigitPattern(12)) << " (expect 12)\n";
    std::cout << BarcodeDecoder::decodeDigitPattern("0000") << " (expect -1)\n";

    // verifyDecodedResult
    std::cout << BarcodeDecoder::verifyDecodedResult("123456") << " (expect 1)\n";
    std::cout << BarcodeDecoder::verifyDecodedResult("023456") << " (expect 0)\n";
    std::cout << BarcodeDecoder::verifyDecodedResult("123456", 44) << " (expect 1)\n";
    std::cout << BarcodeDecoder::verifyDecodedResult("123456", 45) << " (expect 0)\n";

    // full round trip using Rabiya's encoder
    std::string code = BarcodeEncoder::encodeSixDigits("123456");
    std::cout << code.length() << " (expect 68)\n";
    std::cout << InputValidator::validateScannedPattern(code) << " (expect 1)\n";
    std::cout << BarcodeDecoder::decodeDigitPattern(code.substr(11, 11)) << " (expect 12)\n";
    std::cout << BarcodeDecoder::decodeDigitPattern(code.substr(22, 11)) << " (expect 34)\n";
    std::cout << BarcodeDecoder::decodeDigitPattern(code.substr(33, 11)) << " (expect 56)\n";
}