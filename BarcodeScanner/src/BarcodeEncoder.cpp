/*
 * File    : BarcodeEncoder.cpp
 * Purpose : Digit-to-pattern encoding (Member 1)
 */
#include "BarcodeEncoder.h"
#include "InputValidator.h"
using namespace std;
static const char* const PATTERNS[107] = {
"212222", "222122", "222221", "121223", "121322", "131222", "122213", "122312", "132212", "221213", // 0-9
"221312", "231212", "112232", "122132", "122231", "113222", "123122", "123221", "223211", "221132", // 10-19
	"221231","213212", "223112", "312131", "311222", "321122", "321221", "312212", "322112", "322211",//20-29
	"212123","212321", "232121", "111323", "131123", "131321", "112313", "132113", "132311", "211313",//30-39
	"231113","231311", "112133", "112331", "132131", "113123", "113321", "133121", "313121", "211331",//40-49
	"231131","213113", "213311", "213131", "311123", "311321", "331121", "312113", "312311", "332111",//50-59
	"314111","221411", "431111", "111224", "111422", "121124", "121421", "141122", "141221", "112214",//60-69
	"112412","122114", "122411", "142112", "142211", "241211", "221114", "413111", "241112", "134111",//70-79
	"111242","121142", "121241", "114212", "124112", "124211", "411212", "421112", "421211", "212141",//80-89
	"214121","412121", "111143", "111341", "131141", "114113", "114311", "411113", "411311", "113141",//90-99
	"114131","311141", "411131", "211412", "211214", "211232",//100-105
	"2331112"//106->Stop
};
//helper function
std::string BarcodeEncoder::widthsToModules(const std::string& widths) {
	string modules = "";
	//black=1 means black color
	//black=0 means white color 
	char color = '1';
	for (int i = 0;i < widths.length();i++) {
		//converted character to number
		//count tells us how long our module is 
		int count = widths[i] - '0';
		for (int j = 0;j < count;j++) {
			modules += color;
		}
		color = (color == '1') ? '0' : '1';
	}
	return modules;
}
//helper function
std::string BarcodeEncoder::getWidthPattern(int value) {
	bool ok = (value >= 0 && value <= 102) || value == START_C || value == STOP;
	if (!ok) return "";
	return PATTERNS[value];
}
//converts symbol val. to 0/1 pattern
std::string BarcodeEncoder::getDigitPattern(int value)
{
	std::string widths = getWidthPattern(value);
	if (widths.empty())
		return "";
	return widthsToModules(widths);

}
int BarcodeEncoder::calculateSum(int pair1, int pair2, int pair3) {
	return (START_C + pair1 * 1 + pair2 * 2 + pair3 * 3) % 103;
}

std::string BarcodeEncoder::encodeSixDigits(const std::string& sixDigits)
{
	std::string error;
	if (!InputValidator::validateSixDigitInput(sixDigits, error))
	{
		return "";                
	}
	// pairs making ,6 digits -> 3 pairs
	int pairs[3];
	for (int i = 0; i < 3; i++) {
		pairs[i] = (sixDigits[2 * i] - '0') * 10 + (sixDigits[2 * i + 1] - '0');
	}
	int checkSum = calculateSum(pairs[0], pairs[1], pairs[2]);
	string barcode = getDigitPattern(START_C);
	barcode += getDigitPattern(pairs[0]);
	barcode += getDigitPattern(pairs[1]);
	barcode += getDigitPattern(pairs[2]);
	barcode += getDigitPattern(checkSum);
	barcode += getDigitPattern(STOP);
	return barcode;
}
//checks if the table values we entered are correct or not?
bool BarcodeEncoder::verifyPattern() {
	for (int i = 0;i <= STOP;i++) {
		if (PATTERNS[i] == nullptr) return false;
		string str = PATTERNS[i];
		int sum = 0;//should be 11 for every width or 13 for stop  
		for (int j = 0;j < str.length();j++) {
			sum += str[j] - '0';
		}
		if (sum != (i == STOP ? 13 : 11))
			return false;
		//Two symbols should not have same value 
		for (int k = i + 1;k <= STOP;k++) {
			if (PATTERNS[k] != nullptr && str == PATTERNS[k])
				return false;
		}

	}
	return true;
}