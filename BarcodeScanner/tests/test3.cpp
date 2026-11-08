/*
 * File    : TestMember3.cpp
 * Purpose : Test cases for Member 3's functions
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "Config.h"
#include "InputValidator.h"
#include "BarcodeScanner.h"
#include "BMPFileHandler.h"

static int g_passed = 0;
static int g_failed = 0;

static void check(const char* name, bool condition)
{
    if (condition) { g_passed++; std::cout << "[PASS] " << name << "\n"; }
    else { g_failed++; std::cout << "[FAIL] " << name << "\n"; }
}

// Write 'bytes' bytes of 'value' into h at 'pos', lowest byte first (little-endian)
static void putLE(unsigned char* h, int pos, unsigned int value, int bytes)
{
    for (int i = 0; i < bytes; i++)
        h[pos + i] = (unsigned char)((value >> (8 * i)) & 0xFF);
}

// Build a fake 54-byte BMP header with the given values
static void makeHeader(unsigned char h[54], int width, int height, int bitDepth)
{
    std::memset(h, 0, 54);
    h[0] = 'B';
    h[1] = 'M';
    putLE(h, 2, 54u + 3u * (unsigned)width * (unsigned)height, 4);
    putLE(h, 10, 54, 4);          // pixel data offset
    putLE(h, 14, 40, 4);          // info header size
    putLE(h, 18, (unsigned)width, 4);
    putLE(h, 22, (unsigned)height, 4);
    putLE(h, 26, 1, 2);           // planes
    putLE(h, 28, (unsigned)bitDepth, 2);
    putLE(h, 30, 0, 4);           // compression: none
}

static void testValidateBMPHeader()
{
    unsigned char h[54];

    makeHeader(h, 120, 40, 24);
    check("validateBMPHeader: valid header accepted",
        InputValidator::validateBMPHeader(h, 54));

    makeHeader(h, 120, 40, 24);
    h[0] = 'X';
    check("validateBMPHeader: bad signature rejected",
        !InputValidator::validateBMPHeader(h, 54));

    makeHeader(h, 120, 40, 8);
    check("validateBMPHeader: 8-bit rejected",
        !InputValidator::validateBMPHeader(h, 54));

    makeHeader(h, 0, 40, 24);
    check("validateBMPHeader: width 0 rejected",
        !InputValidator::validateBMPHeader(h, 54));

    makeHeader(h, MAX_WIDTH + 1, 40, 24);
    check("validateBMPHeader: width above MAX_WIDTH rejected",
        !InputValidator::validateBMPHeader(h, 54));

    makeHeader(h, 120, 40, 24);
    check("validateBMPHeader: buffer of 20 bytes rejected",
        !InputValidator::validateBMPHeader(h, 20));
}

void runMember3Tests()
{
    std::cout << "\n--- Member 3 Tests ---\n";
    testValidateBMPHeader();
}