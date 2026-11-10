#pragma once
#ifndef BARCODESYSTEM_H
#define BARCODESYSTEM_H
#include "InputValidator.h"
#include "BarcodeEncoder.h"
#include "BarcodeRenderer.h"
#include "BarcodeDecoder.h"
#include "BMPFileHandler.h"
#include "BarcodeScanner.h"
#include "Config.h"
class BarcodeSystem
{
	InputValidator validator;
	BarcodeEncoder encoder;
	BarcodeRenderer renderer;
	BarcodeDecoder decoder;
	BarcodeScanner scanner;
	BMPFileHandler bmpHandler;

public:
	void generateBarcode(string input);
	void showMenu();
	void decodeBarcode(string filename);
};
#endif