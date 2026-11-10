/*
 * File    : InputValidator.cpp
 * Purpose : Implements validation functions (shared by 4 members)
 */
#include<iostream>
#include "InputValidator.h"
using namespace std;
//hepler functions -member1
bool InputValidator::isEmpty(const string& s) {
	return s.empty();
}
bool InputValidator::isNumeric(const string& s) {
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}
bool InputValidator::hasValidLength(const string& s) {
	return s.length() == 6;
}
bool InputValidator::validateSixDigitInput(const string& s, string& errorMessage)
{
	errorMessage = "";
	if (isEmpty(s)) {
		errorMessage = "Input is empty. Please enter a 6-digit number.";
		return false;
	}
	if (!isNumeric(s)) {
		errorMessage = "Input must contain digits (0-9) only.";
		return false;
	}
	if (!hasValidLength(s)) {
		errorMessage = "Input must be exactly 6 digits (you entered "
			+ to_string(s.length()) + ").";
		return false;
	}
	if (s[0] == '0') {
		errorMessage = "The first digit must be non-zero.";
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