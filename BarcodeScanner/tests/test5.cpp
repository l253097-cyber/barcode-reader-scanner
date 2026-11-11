/*
 * File    : TestMember2.cpp
 * Purpose : Test cases for Member 2's functions
 */

#include <iostream>
#include <string>
#include "BarcodeDecoder.h"
#include "BarcodeEncoder.h"

using namespace std;

static int passed = 0, failed = 0;

#define CHECK(cond, name)                                         \
    do {                                                          \
        if (cond) { passed++; }                                   \
        else { failed++; cout << "FAIL: " << name << "\n"; }      \
    } while (0)

// Helper: encode a number to get a valid barcode for testing
static string makeBarcode(string number)
{
    return BarcodeEncoder::encodeSixDigits(number);
}

// Helper: double the width of every module
static string scalePattern(string pattern)
{
    string result = "";

    for (int i = 0; i < pattern.length(); i++)
    {
        result += pattern[i];
        result += pattern[i];
    }

    return result;
}

// ===================== Normal decoding =====================

static void testNormalDecoding()
{
    BarcodeDecoder decoder;

    CHECK(decoder.decodeScannedPattern(makeBarcode("123456")) == "123456",
        "decode 123456");

    CHECK(decoder.decodeScannedPattern(makeBarcode("987654")) == "987654",
        "decode 987654");

    CHECK(decoder.decodeScannedPattern(makeBarcode("999999")) == "999999",
        "decode 999999");

    CHECK(decoder.decodeScannedPattern(makeBarcode("100000")) == "100000",
        "decode zeros inside number");

    CHECK(decoder.decodeScannedPattern(makeBarcode("102030")) == "102030",
        "decode 102030");

    CHECK(decoder.decodeScannedPattern(makeBarcode("100129")) == "100129",
        "decode number with checksum above 99");
}

// ===================== Invalid input =====================

static void testInvalidInput()
{
    BarcodeDecoder decoder;

    CHECK(decoder.decodeScannedPattern("").empty(),
        "empty pattern rejected");

    CHECK(decoder.decodeScannedPattern("ABC123").empty(),
        "letters rejected");

    CHECK(decoder.decodeScannedPattern("123456").empty(),
        "decimal number rejected");

    CHECK(decoder.decodeScannedPattern("11010A111").empty(),
        "invalid character inside pattern");

    string allZeros(68, '0');

    CHECK(decoder.decodeScannedPattern(allZeros).empty(),
        "pattern with no black bars rejected");

    CHECK(decoder.decodeScannedPattern(string(50, '1')).empty(),
        "incorrect length rejected");
}

// ===================== Start and Stop validation =====================

static void testStartAndStop()
{
    BarcodeDecoder decoder;

    string barcode = makeBarcode("123456");

    // Replace Start C with another valid symbol
    string wrongStart = barcode;
    wrongStart.replace(0, 11, BarcodeEncoder::getDigitPattern(1));

    CHECK(decoder.decodeScannedPattern(wrongStart).empty(),
        "wrong Start C rejected");

    // Replace Stop with zeros
    string wrongStop = barcode;
    wrongStop.replace(55, 13, string(13, '0'));

    CHECK(decoder.decodeScannedPattern(wrongStop).empty(),
        "wrong Stop pattern rejected");

    // Remove one module
    string wrongLength = barcode;
    wrongLength.erase(wrongLength.length() - 1);

    CHECK(decoder.decodeScannedPattern(wrongLength).empty(),
        "barcode with missing module rejected");
}

// ===================== Data symbol and checksum =====================

static void testSymbolsAndChecksum()
{
    BarcodeDecoder decoder;

    string barcode = makeBarcode("123456");

    // Change first data pair to Code 128 value 100.
    // Value 100 is not a valid digit pair (0-99).
    string invalidData = barcode;
    invalidData.replace(11, 11, BarcodeEncoder::getDigitPattern(100));

    CHECK(decoder.decodeScannedPattern(invalidData).empty(),
        "invalid data symbol rejected");

    // Change checksum to another valid symbol
    string wrongChecksum = barcode;

    int checksum = BarcodeEncoder::calculateSum(12, 34, 56);
    int incorrectChecksum = (checksum + 1) % 103;

    wrongChecksum.replace(44, 11,
        BarcodeEncoder::getDigitPattern(incorrectChecksum));

    CHECK(decoder.decodeScannedPattern(wrongChecksum).empty(),
        "wrong checksum rejected");

    // Check that a valid checksum is accepted
    CHECK(decoder.decodeScannedPattern(barcode) == "123456",
        "correct checksum accepted");
}

// ===================== Pattern normalization =====================

static void testNormalization()
{
    BarcodeDecoder decoder;

    string barcode = makeBarcode("123456");

    // Barcode with doubled module widths
    string scaled = scalePattern(barcode);

    CHECK(decoder.decodeScannedPattern(scaled) == "123456",
        "scaled barcode accepted");

    // Barcode with white quiet zones at both ends
    string quietZone = "00000000" + barcode + "00000000";

    CHECK(decoder.decodeScannedPattern(quietZone) == "123456",
        "leading and trailing quiet zones accepted");

    // Scaled barcode with quiet zones
    string scaledQuietZone = "000000" + scaled + "000000";

    CHECK(decoder.decodeScannedPattern(scaledQuietZone) == "123456",
        "scaled barcode with quiet zones accepted");
}

// ===================== Main =====================

int main()
{
    testNormalDecoding();
    testInvalidInput();
    testStartAndStop();
    testSymbolsAndChecksum();
    testNormalization();

    cout << "\n========== Decoder Test Results ==========\n";
    cout << "Passed: " << passed << "  Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
