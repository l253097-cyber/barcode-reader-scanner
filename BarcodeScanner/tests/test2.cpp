/*
 * File    : test2.cpp
 * Purpose : Tests for Member 2 (validateEncodedData, createPixelMatrix,
 *           renderBarcode, writeBMPPixelData) using Code 128 strings
 */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "InputValidator.h"
#include "BarcodeRenderer.h"
#include "BMPFileHandler.h"
#include "Config.h"

static int passed = 0;
static int failed = 0;

static void check(const char* name, bool condition)
{
    if (condition)
    {
        std::cout << "  [PASS] " << name << "\n";
        passed++;
    }
    else
    {
        std::cout << "  [FAIL] " << name << "\n";
        failed++;
    }
}

// ---- Code 128 building blocks used by the tests ----
static const std::string START_C = "11010011100";    // Start Code C
static const std::string STOP = "1100011101011";  // Stop pattern
static const std::string SYM_0 = "11011001100";    // symbol value 0
static const std::string SYM_1 = "11001101100";    // symbol value 1
static const std::string SYM_2 = "11001100110";    // symbol value 2

void runMember2Tests()
{
    std::cout << "\n--- Member 2 Tests ---\n";
    passed = 0;
    failed = 0;

    // A small valid Code 128 string: start + 3 symbols + stop = 57 modules
    std::string valid = START_C + SYM_0 + SYM_1 + SYM_2 + STOP;
    static int matrix[MAX_HEIGHT][MAX_WIDTH];
    int w = 0, h = 0;

    // ---------- validateEncodedData ----------
    std::cout << "validateEncodedData:\n";
    check("valid Code 128 string", InputValidator::validateEncodedData(valid));
    check("empty string rejected", !InputValidator::validateEncodedData(""));
    check("letter inside rejected",
        !InputValidator::validateEncodedData(START_C + "1100110011a" + STOP));
    check("digit 2 rejected",
        !InputValidator::validateEncodedData(START_C + "11001100112" + STOP));
    check("all zeros rejected",
        !InputValidator::validateEncodedData(std::string(57, '0')));
    check("too long rejected",
        !InputValidator::validateEncodedData(std::string(MAX_ENCODED_LEN + 1, '1')));
    check("missing start pattern rejected",
        !InputValidator::validateEncodedData("00000000000" + SYM_0 + SYM_1 + STOP));
    check("missing stop pattern rejected",
        !InputValidator::validateEncodedData(START_C + SYM_0 + SYM_1 + "1111111111111"));
    check("wrong length rejected",
        !InputValidator::validateEncodedData(START_C + SYM_0 + SYM_1 + "1" + STOP));

    // ---------- createPixelMatrix ----------
    std::cout << "createPixelMatrix:\n";
    bool ok = BarcodeRenderer::createPixelMatrix(valid, 2, 3, matrix, w, h);
    check("returns true for valid input", ok);
    check("width is 114 (57 modules x 2)", w == 114);
    check("height is 3", h == 3);
    // START_C = 1 1 0 1 0 0 1 1 1 0 0
    check("modules 0-1 black (columns 0-3)",
        matrix[0][0] == 1 && matrix[0][1] == 1 && matrix[0][2] == 1 && matrix[0][3] == 1);
    check("module 2 white (columns 4-5)", matrix[0][4] == 0 && matrix[0][5] == 0);
    check("module 3 black (columns 6-7)", matrix[0][6] == 1 && matrix[0][7] == 1);
    check("last row same as first row", matrix[2][0] == 1 && matrix[2][4] == 0);
    check("last column is black (stop pattern)", matrix[0][113] == 1);
    check("invalid data rejected",
        !BarcodeRenderer::createPixelMatrix("1a1", 2, 3, matrix, w, h));
    check("moduleWidth 0 rejected",
        !BarcodeRenderer::createPixelMatrix(valid, 0, 3, matrix, w, h));
    check("height 0 rejected",
        !BarcodeRenderer::createPixelMatrix(valid, 2, 0, matrix, w, h));
    check("too wide rejected (57 x 11 = 627 > 600)",
        !BarcodeRenderer::createPixelMatrix(valid, 11, 3, matrix, w, h));

    // ---------- renderBarcode ----------
    // moduleWidth 2, height 3, quietZone 20 -> width = 20 + 114 + 20 = 154
    std::cout << "renderBarcode:\n";
    ok = BarcodeRenderer::renderBarcode(valid, 2, 3, 20, matrix, w, h);
    check("returns true for valid input", ok);
    check("width is 154 (20 + 114 + 20)", w == 154);
    check("height is 3", h == 3);
    check("left quiet zone is white", matrix[0][0] == 0 && matrix[0][19] == 0);
    check("first bar starts at column 20", matrix[0][20] == 1 && matrix[0][23] == 1);
    check("first space is at columns 24-25", matrix[0][24] == 0 && matrix[0][25] == 0);
    check("barcode ends black at column 133", matrix[0][133] == 1);
    check("right quiet zone is white", matrix[0][134] == 0 && matrix[0][153] == 0);
    check("negative quietZone rejected",
        !BarcodeRenderer::renderBarcode(valid, 2, 3, -1, matrix, w, h));
    check("invalid data rejected",
        !BarcodeRenderer::renderBarcode("101", 2, 3, 20, matrix, w, h));
    check("moduleWidth 0 rejected",
        !BarcodeRenderer::renderBarcode(valid, 0, 3, 20, matrix, w, h));
    check("height above MAX_HEIGHT rejected",
        !BarcodeRenderer::renderBarcode(valid, 2, MAX_HEIGHT + 1, 20, matrix, w, h));
    check("quietZone too large rejected (114 + 600 > 600)",
        !BarcodeRenderer::renderBarcode(valid, 2, 3, 300, matrix, w, h));

    // ---------- writeBMPPixelData ----------
    // Image 114 x 3: row = 342 bytes + 2 padding = 344, file = 54 + 3 x 344 = 1086
    std::cout << "writeBMPPixelData:\n";
    BarcodeRenderer::createPixelMatrix(valid, 2, 3, matrix, w, h);
    const char* fileName = "test_member2.bmp";
    {
        std::ofstream out(fileName, std::ios::binary);
        //dummy 54 -- see mem1
        for (int i = 0; i < 54; i++)
        {
            out.put(0);
        }
        check("pixel data written", BMPFileHandler::writeBMPPixelData(out, matrix, w, h));
    }
    static unsigned char data[1200];
    std::ifstream in(fileName, std::ios::binary);
    in.read((char*)data, 1200);
    int bytesRead = (int)in.gcount();
    in.close();

    check("file size is 54 + 1032 = 1086", bytesRead == 1086);
    check("first pixel is black",
        data[54] == 0 && data[55] == 0 && data[56] == 0);
    check("pixel at column 4 is white",
        data[66] == 255 && data[67] == 255 && data[68] == 255);
    check("padding bytes are 0", data[396] == 0 && data[397] == 0);
}