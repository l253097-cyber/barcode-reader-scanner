/*
 * File    : InputValidator.cpp
 * Purpose : Implements validation functions (shared by 4 members)
 */
#include "InputValidator.h"
#include<iostream>
using namespace std;
 // ===== Member 1: validateSixDigitInput =====
bool InputValidator::validateSixDigitInput(string& input)
{
        // 1. empty
        if (input.empty()) {
            cout << "Error: Input is empty. Please enter a 6-digit number.\n";
            return false;
        }

        // 2. digits only (catches letters, spaces, dots, + and -)
        for (size_t i = 0; i < input.length(); i++) {
            if (input[i] < '0' || input[i] > '9') {
                cout << "Error: Input must contain digits (0-9) only.\n";
                return false;
            }
        }

        // 3. exactly 6 digits
        if (input.length() != 6) {
            cout << "Error: Input must be exactly 6 digits (you entered "
                << input.length() << ").\n";
            return false;
        }

        // 4. first digit must be non-zero
        if (input[0] == '0') {
            cout << "Error: The first digit must be non-zero.\n";
            return false;
        }

        return true;

}



// ===== Member 2: validateEncodedData =====
bool InputValidator::validateEncodedData(const std::string& encoded)
{
    // TODO (Member 2)
    return false;
}



// ===== Member 3: validateBMPHeader =====
bool InputValidator::validateBMPHeader(const unsigned char header[], int size)
{
    // TODO (Member 3)
    return false;
}



// ===== Member 4: validateScannedPattern =====
bool InputValidator::validateScannedPattern(const std::string& pattern)
{
    // TODO (Member 4)
    return false;
}