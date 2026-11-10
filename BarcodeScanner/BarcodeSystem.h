#pragma once
#include "InputValidator.h"

class BarcodeSystem
{
	InputValidator validator;


	void generateBarcode(string input);
	void showMenu();
};