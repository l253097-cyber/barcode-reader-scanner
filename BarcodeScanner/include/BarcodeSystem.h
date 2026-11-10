#pragma once
#ifndef BARCODESYSTEM_H
#define BARCODESYSTEM_H
#include "InputValidator.h"
#include "BarcodeEncoder.h"
class BarcodeSystem
{
	InputValidator validator;
	BarcodeEncoder encoder;

public:
	void generateBarcode(string input);
	void showMenu();
};
#endif