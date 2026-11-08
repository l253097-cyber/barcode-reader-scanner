// tests/test1.cpp - Member 1 tests (InputValidator + BarcodeEncoder + BMPFileHandler)
#include <iostream>
#include <fstream>
#include <string>
#include "InputValidator.h"
#include "BarcodeEncoder.h"
#include "BMPFileHandler.h"

static int passed = 0, failed = 0;

#define CHECK(cond, name)                                         \
    do {                                                          \
        if (cond) { passed++; }                                   \
        else { failed++; std::cout << "FAIL: " << name << "\n"; } \
    } while (0)

static bool validate(const std::string& s) {
    std::string err;
    return InputValidator::validateSixDigitInput(s, err);
}

// ===================== InputValidator =====================
static void testValidator() {
    // valid
    CHECK(validate("123456"), "valid 123456");
    CHECK(validate("000000"), "valid 000000");
    CHECK(validate("012345"), "valid leading zero");
    CHECK(validate("999999"), "valid 999999");

    // invalid
    CHECK(!validate(""), "empty rejected");
    CHECK(!validate("12345"), "5 digits rejected");
    CHECK(!validate("1234567"), "7 digits rejected");
    CHECK(!validate("12a456"), "letter inside rejected");
    CHECK(!validate("abcdef"), "all letters rejected");
    CHECK(!validate(" 12345"), "leading space rejected");
    CHECK(!validate("12 456"), "space inside rejected");
    CHECK(!validate("123456 "), "trailing space rejected");
    CHECK(!validate("12.456"), "dot rejected");
    CHECK(!validate("-12345"), "minus sign rejected");
    CHECK(!validate("+12345"), "plus sign rejected");

    // helpers
    CHECK(InputValidator::isEmpty(""), "isEmpty on empty");
    CHECK(!InputValidator::isEmpty("1"), "isEmpty on non-empty");
    CHECK(InputValidator::isNumeric("0123456789"), "isNumeric digits");
    CHECK(!InputValidator::isNumeric("12a4"), "isNumeric with letter");
    CHECK(InputValidator::hasValidLength("123456"), "length 6 ok");
    CHECK(!InputValidator::hasValidLength("12345"), "length 5 rejected");

    // error messages
    std::string err;
    InputValidator::validateSixDigitInput("", err);
    CHECK(!err.empty(), "message for empty input");
    InputValidator::validateSixDigitInput("12a456", err);
    CHECK(!err.empty(), "message for letters");
    InputValidator::validateSixDigitInput("12345", err);
    CHECK(!err.empty(), "message for wrong length");
    InputValidator::validateSixDigitInput("123456", err);
    CHECK(err.empty(), "no message when valid");
}

// ===================== BarcodeEncoder: table and symbols =====================
static void testEncoderSoFar() {
    // widths -> modules
    CHECK(BarcodeEncoder::widthsToModules("212222") == "11011001100", "widths 212222");
    CHECK(BarcodeEncoder::widthsToModules("112232") == "10110011100", "widths 112232");
    CHECK(BarcodeEncoder::widthsToModules("2331112") == "1100011101011", "widths 2331112 (Stop)");
    CHECK(BarcodeEncoder::widthsToModules("211232") == "11010011100", "widths 211232 (Start C)");

    // getDigitPattern: value -> modules
    CHECK(BarcodeEncoder::getDigitPattern(0) == "11011001100", "pair 00");
    CHECK(BarcodeEncoder::getDigitPattern(12) == "10110011100", "pair 12");
    CHECK(BarcodeEncoder::getDigitPattern(99) == "10111011110", "pair 99");
    CHECK(BarcodeEncoder::getDigitPattern(105) == "11010011100", "Start C");
    CHECK(BarcodeEncoder::getDigitPattern(106) == "1100011101011", "Stop");

    // every pair pattern: 11 modules, starts with a bar, ends with a space
    for (int v = 0; v <= 99; v++) {
        std::string m = BarcodeEncoder::getDigitPattern(v);
        CHECK(m.length() == 11 && m[0] == '1' && m[10] == '0',
            "pair pattern shape " + std::to_string(v));
    }

    // invalid symbol values return an empty string
    CHECK(BarcodeEncoder::getDigitPattern(-1).empty(), "value -1 rejected");
    CHECK(BarcodeEncoder::getDigitPattern(103).empty(), "value 103 rejected");
    CHECK(BarcodeEncoder::getDigitPattern(107).empty(), "value 107 rejected");

    // checksum can be 100..102, so these symbols must exist
    CHECK(BarcodeEncoder::getDigitPattern(100).length() == 11, "value 100 exists");
    CHECK(BarcodeEncoder::getDigitPattern(102).length() == 11, "value 102 exists");

    // table self-check: every width sums to 11 (Stop 13), no duplicates
    CHECK(BarcodeEncoder::verifyPattern(), "table sums + no duplicates");
}

// ===================== BarcodeEncoder: checksum and full encoding =====================
static void testEncoderFull() {
    // checksum = (105 + 1*v1 + 2*v2 + 3*v3) % 103
    CHECK(BarcodeEncoder::calculateSum(12, 34, 56) == 44, "checksum 123456");
    CHECK(BarcodeEncoder::calculateSum(0, 0, 0) == 2, "checksum 000000");
    CHECK(BarcodeEncoder::calculateSum(0, 99, 70) == 101, "checksum 009970 (value above 99)");

    // complete sequence for 123456
    std::string s = BarcodeEncoder::encodeSixDigits("123456");
    CHECK(s == "11010011100101100111001000101100011100010110100011011101100011101011",
        "full sequence 123456");
    CHECK(s.length() == 68, "length 68");
    CHECK(s.substr(0, 11) == BarcodeEncoder::getDigitPattern(105), "starts with Start C");
    CHECK(s.substr(11, 11) == BarcodeEncoder::getDigitPattern(12), "pair 12");
    CHECK(s.substr(22, 11) == BarcodeEncoder::getDigitPattern(34), "pair 34");
    CHECK(s.substr(33, 11) == BarcodeEncoder::getDigitPattern(56), "pair 56");
    CHECK(s.substr(44, 11) == BarcodeEncoder::getDigitPattern(44), "checksum symbol 44");
    CHECK(s.substr(55, 13) == BarcodeEncoder::getDigitPattern(106), "ends with Stop");

    // leading zeros keep their place: 012345 -> pairs 01, 23, 45
    std::string z = BarcodeEncoder::encodeSixDigits("012345");
    CHECK(z.length() == 68, "012345 length 68");
    CHECK(z.substr(11, 11) == BarcodeEncoder::getDigitPattern(1), "012345 first pair 01");
    CHECK(z.substr(22, 11) == BarcodeEncoder::getDigitPattern(23), "012345 second pair 23");

    // checksum symbol above 99 (009970 -> checksum 101)
    std::string c = BarcodeEncoder::encodeSixDigits("009970");
    CHECK(c.length() == 68, "009970 length 68");
    CHECK(c.substr(44, 11) == BarcodeEncoder::getDigitPattern(101), "009970 checksum symbol 101");

    // different numbers give different barcodes
    CHECK(BarcodeEncoder::encodeSixDigits("012345") != BarcodeEncoder::encodeSixDigits("123450"),
        "different numbers, different barcodes");

    // invalid input gives an empty string
    CHECK(BarcodeEncoder::encodeSixDigits("").empty(), "encode empty");
    CHECK(BarcodeEncoder::encodeSixDigits("12345").empty(), "encode 5 digits");
    CHECK(BarcodeEncoder::encodeSixDigits("1234567").empty(), "encode 7 digits");
    CHECK(BarcodeEncoder::encodeSixDigits("12a456").empty(), "encode letters");
}

// ===================== BMPFileHandler: header =====================
static unsigned int readLE(const unsigned char* b, int pos, int n) {
    unsigned int v = 0;
    for (int i = 0; i < n; i++)
        v |= (unsigned int)b[pos + i] << (8 * i);
    return v;
}

static void testBMPHeader() {
    {   // inner scope, so the file is closed before we read it back
        std::ofstream out("header_test.bmp", std::ios::binary);
        CHECK(BMPFileHandler::writeBMPHeader(out, 250, 100), "header written");
    }
    std::ifstream in("header_test.bmp", std::ios::binary);
    unsigned char b[60] = { 0 };
    in.read((char*)b, 60);
    CHECK(in.gcount() == 54, "header is exactly 54 bytes");
    CHECK(b[0] == 'B' && b[1] == 'M', "signature BM");
    CHECK(readLE(b, 2, 4) == 75254, "file size (54 + 752*100)");
    CHECK(readLE(b, 6, 4) == 0, "reserved");
    CHECK(readLE(b, 10, 4) == 54, "pixel offset");
    CHECK(readLE(b, 14, 4) == 40, "info header size");
    CHECK(readLE(b, 18, 4) == 250, "width");
    CHECK(readLE(b, 22, 4) == 100, "height");
    CHECK(readLE(b, 26, 2) == 1, "planes");
    CHECK(readLE(b, 28, 2) == 24, "bit depth");
    CHECK(readLE(b, 30, 4) == 0, "compression");
    CHECK(readLE(b, 34, 4) == 75200, "image size (752*100)");
    CHECK(readLE(b, 38, 4) == 2835, "horizontal resolution");
    CHECK(readLE(b, 42, 4) == 2835, "vertical resolution");

    // bad sizes are rejected
    std::ofstream bad("bad_test.bmp", std::ios::binary);
    CHECK(!BMPFileHandler::writeBMPHeader(bad, 0, 100), "width 0 rejected");
    CHECK(!BMPFileHandler::writeBMPHeader(bad, 100, 0), "height 0 rejected");
    CHECK(!BMPFileHandler::writeBMPHeader(bad, 100, -5), "negative height rejected");
    CHECK(!BMPFileHandler::writeBMPHeader(bad, MAX_WIDTH + 1, 100), "too wide rejected");
    CHECK(!BMPFileHandler::writeBMPHeader(bad, 100, MAX_HEIGHT + 1), "too tall rejected");
    CHECK(BMPFileHandler::writeBMPHeader(bad, MAX_WIDTH, MAX_HEIGHT), "max size accepted");
}

int main() {
    testValidator();
    testEncoderSoFar();
    testEncoderFull();
    testBMPHeader();

    std::cout << "Passed: " << passed << "  Failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}