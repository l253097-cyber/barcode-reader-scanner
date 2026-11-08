#pragma once
#include<string>
class InputValidator
{
public:
	static const int digit_count = 6;
	static const int modules_per_digit = 7;
	static const int expected_length = 68;
	static bool validateScannerPatern(const std::string& pattern);
};