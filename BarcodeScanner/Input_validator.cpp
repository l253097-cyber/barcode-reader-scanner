#include"Input_validator.h"
bool InputValidator::validateScannerPatern(const std::string& pattern)
{
	if (pattern.empty())
		return false;
	if (pattern.length() != expected_length)
		return false;
	for (int i = 0;i < pattern.length();i++)
	{
		if (pattern[i] != '0' && pattern[i] != '1')
			return false;
	}
	return true;
}