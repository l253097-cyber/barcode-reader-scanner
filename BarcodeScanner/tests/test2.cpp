/*
 * File    : test2.cpp
 * Purpose : Tests for Member 2 (validateEncodedData, createPixelMatrix)
 */
#include <iostream>
#include <string>
#include "InputValidator.h"
#include "BarcodeRenderer.h"
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

void runMember2Tests()
{
    std::cout << "\n--- Member 2 Tests ---\n";
    passed = 0;
    failed = 0;

    // "static" keeps this big array off the stack (avoids stack overflow)
    static int matrix[MAX_HEIGHT][MAX_WIDTH];
    int w = 0, h = 0;

    // ---------- validateEncodedData ----------
    std::cout << "validateEncodedData:\n";
    check("valid string 10101", InputValidator::validateEncodedData("10101"));
    check("empty string rejected", !InputValidator::validateEncodedData(""));
    check("letter inside rejected", !InputValidator::validateEncodedData("10a01"));
    check("digit 2 rejected", !InputValidator::validateEncodedData("10201"));
    check("all zeros rejected", !InputValidator::validateEncodedData("00000"));
    check("too long rejected",
        !InputValidator::validateEncodedData(std::string(MAX_ENCODED_LEN + 1, '1')));

    // ---------- createPixelMatrix ----------
    std::cout << "createPixelMatrix:\n";
    bool ok = BarcodeRenderer::createPixelMatrix("101", 2, 3, matrix, w, h);
    check("returns true for valid input", ok);
    check("width is 6 (3 modules x 2)", w == 6);
    check("height is 3", h == 3);
    check("columns 0-1 are black", matrix[0][0] == 1 && matrix[0][1] == 1);
    check("columns 2-3 are white", matrix[0][2] == 0 && matrix[0][3] == 0);
    check("columns 4-5 are black", matrix[0][4] == 1 && matrix[0][5] == 1);
    check("last row same as first row", matrix[2][0] == 1 && matrix[2][2] == 0);
    check("invalid data rejected",
        !BarcodeRenderer::createPixelMatrix("1a1", 2, 3, matrix, w, h));
    check("moduleWidth 0 rejected",
        !BarcodeRenderer::createPixelMatrix("101", 0, 3, matrix, w, h));
    check("height 0 rejected",
        !BarcodeRenderer::createPixelMatrix("101", 2, 0, matrix, w, h));
    check("too wide rejected (200 x 4 = 800 > 600)",
        !BarcodeRenderer::createPixelMatrix(std::string(200, '1'), 4, 3, matrix, w, h));

    std::cout << "Result: " << passed << " passed, " << failed << " failed\n";
}
