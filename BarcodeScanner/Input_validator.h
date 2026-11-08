#pragma once
#include<string>
class InputValidator
{
public:
	static const int digit_count = 6;
	static bool validateScannerPatern(const std::string& pattern);
};