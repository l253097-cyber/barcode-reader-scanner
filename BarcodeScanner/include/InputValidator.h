/*
 * File    : InputValidator.h
 * Purpose : Declares all validation functions used across the project.
 * Note    : Shared file - each member edits ONLY their own function body.
 */
#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>
using namespace std;
#include "Config.h"

class InputValidator
{
public:
    // Member 1: checks user input is exactly 6 digits
		//checks for if string is empty 
		static bool isEmpty(const std::string& s);
		//checks for if string consists of all numbers
		static bool isNumeric(const std::string& s);
		//checks for if string has valid length of 6
		static bool hasValidLength(const std::string& s);
		//keeping in view above 3 functions it validates the input and returns error message if any of the above 3 conditions are not met
		static bool  validateSixDigitInput(const std::string& s, std::string& errorMessage);

    // Member 2: checks encoded sequence contains only '0'/'1' and is valid
    static bool validateEncodedData(const std::string& encoded);

    // Member 3: checks the 54-byte BMP header (signature, bit depth, etc.)
    static bool validateBMPHeader(const unsigned char header[], int size);

    // Member 4: checks pattern received from scanner
    static bool validateScannedPattern(const std::string& pattern);
};

#endif