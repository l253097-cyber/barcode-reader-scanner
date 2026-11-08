#pragma once
#include<string>
class InputValidator
{
public:
	static const int expected_length = 68;
	static bool validateScannerPatern(const std::string& pattern);
};