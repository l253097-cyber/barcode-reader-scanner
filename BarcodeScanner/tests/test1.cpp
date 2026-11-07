// tests/test1.cpp - Member 1 tests (InputValidator + BarcodeEncoder)
#include <iostream>
#include <string>
#include "InputValidator.h"
#include "BarcodeEncoder.h"

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
static void testEncoderSoFar() {
    // widths -> modules (expected values from the Code 128 table)
    // (if widthsToModules is private, remove these 3 checks; getDigitPattern below covers it)
    CHECK(BarcodeEncoder::widthsToModules("212222") == "11011001100", "widths 212222");
    CHECK(BarcodeEncoder::widthsToModules("112232") == "10110011100", "widths 112232");
    CHECK(BarcodeEncoder::widthsToModules("2331112") == "1100011101011", "widths 2331112 (stop)");
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

    //table self-check (if you wrote verifyPatternTable)
    CHECK(BarcodeEncoder::verifyPattern(), "table sums + no duplicates");
}


static void testEncoderFull() {
    CHECK(BarcodeEncoder::calculateSum(12, 34, 56) == 44, "checksum 123456");
    CHECK(BarcodeEncoder::calculateSum(0, 0, 0) == 2, "checksum 000000");

    std::string s = BarcodeEncoder::encodeSixDigits("123456");
    CHECK(s == "11010011100101100111001000101100011100010110100011011101100011101011",
        "full sequence 123456");
    CHECK(s.length() == 68, "length 68");
    CHECK(s.substr(0, 11) == BarcodeEncoder::getDigitPattern(105), "starts with Start C");
    CHECK(s.substr(11, 11) == BarcodeEncoder::getDigitPattern(12), "pair 12");
    CHECK(s.substr(55, 13) == BarcodeEncoder::getDigitPattern(106), "ends with Stop");

    //leading zeros keep their place: 012345 -> pairs 01, 23, 45
    std::string z = BarcodeEncoder::encodeSixDigits("012345");
    CHECK(z.substr(11, 11) == BarcodeEncoder::getDigitPattern(1), "012345 first pair 01");
    CHECK(z.substr(22, 11) == BarcodeEncoder::getDigitPattern(23), "012345 second pair 23");

    //invalid input gives empty string
    CHECK(BarcodeEncoder::encodeSixDigits("").empty(), "encode empty");
    CHECK(BarcodeEncoder::encodeSixDigits("12345").empty(), "encode 5 digits");
    CHECK(BarcodeEncoder::encodeSixDigits("12a456").empty(), "encode letters");
}


int main() {
    testValidator();
    testEncoderSoFar();
    testEncoderFull();   

    std::cout << "Passed: " << passed << "  Failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}