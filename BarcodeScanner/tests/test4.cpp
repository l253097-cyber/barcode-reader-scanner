/*
 * File    : TestMember4.cpp
 * Purpose : Test cases for Member 4's functions
 */
#include <iostream>
#include <fstream>
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
    //test readBmp pixels
    unsigned char header[54] = {
       'B','M', 70,0,0,0, 0,0,0,0, 54,0,0,0,
       40,0,0,0, 2,0,0,0, 2,0,0,0, 1,0, 24,0,
       0,0,0,0, 16,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };
    unsigned char pixels[16] = {
        0,0,0,  255,255,255, 0,0,        // bottom row: black, white (+2 padding)
        255,255,255, 0,0,0,  0,0 };      // top row: white, black (+2 padding)
    {
        std::ofstream out("tiny.bmp", std::ios::binary);
        out.write(reinterpret_cast<char*>(header), 54);
        out.write(reinterpret_cast<char*>(pixels), 16);
    }
    {
        std::ifstream in("tiny.bmp", std::ios::binary);
        int matrix[2][MAX_WIDTH] = {};
        bool ok = BMPFileHandler::readBMPPixelData(in, matrix, 2, 2, 54);

        std::cout << ok << " (expect 1)\n";
        std::cout << matrix[0][0] << matrix[0][1] << " (expect 01, top row)\n";
        std::cout << matrix[1][0] << matrix[1][1] << " (expect 10, bottom row)\n";
    }
    std::remove("tiny.bmp");   // delete the temporary file so it isn't committed

}

