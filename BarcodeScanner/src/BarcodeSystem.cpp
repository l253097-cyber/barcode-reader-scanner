#include<iostream>
#include<fstream>
#include<string>
#include "BarcodeSystem.h"

using namespace std;
void BarcodeSystem::generateBarcode(string input)
{
    string error_message="";

	if (!validator.validateSixDigitInput(input,error_message))
	{
        cout << error_message << endl;
		return;
	}
    string pattern = encoder.encodeSixDigits(input);
    if (pattern.empty())
    {
        cout << "Error: encoding failed.\n";
        return;
    }


    int moduleWidth = 2;
    int barHeight = 100;
    int quietZone = 20;

    static int matrix[MAX_HEIGHT][MAX_WIDTH];
    int imgWidth = 0, imgHeight = 0;

    if (!renderer.renderBarcode(pattern, moduleWidth, barHeight, quietZone,
        matrix, imgWidth, imgHeight))
    {
        cout << "Error: could not render barcode.\n";
        return;
    }

    //  Create BMP file
    string filename = input + ".bmp";

    ofstream file(filename, ios::binary);

    if (!file.is_open())
    {
        cout << "Error: could not create BMP file.\n";
        return;
    }

    if (!bmpHandler.writeBMPHeader(file, imgWidth, imgHeight))
    {
        cout << "Error: could not write BMP header.\n";
        file.close();
        return;
    }

    if (!bmpHandler.writeBMPPixelData(file, matrix,
        imgWidth, imgHeight))
    {
        cout << "Error: could not write BMP pixel data.\n";
        file.close();
        return;
    }

    file.close();

    cout << "Barcode generated successfully!\n";
    cout << "Saved as: " << filename << endl;
}
//void BarcodeSystem::decodeBarcode(string filename)
//{
//    ifstream file(filename, ios::binary);
//    if (!file.is_open())
//    {
//        cout << "Error: could not open file.\n";
//        return;
//    }
//
//    unsigned char header[54];
//    file.read((char*)header, 54);
//    if (file.gcount() != 54 || !validator.validateBMPHeader(header, 54))
//    {
//        cout << "Error: invalid BMP file.\n";
//        return;
//    }
//
//    int imgWidth = 0, imgHeight = 0, bitDepth = 0, pixelOffset = 0;
//
//    if (!bmpHandler.readBMPHeader(file, imgWidth, imgHeight, bitDepth, pixelOffset))
//    {
//        cout << "Error: invalid BMP file.\n";
//        file.close();
//        return;
//    }
//
//    static int matrix[MAX_HEIGHT][MAX_WIDTH];
//
//    if (!bmpHandler.readBMPPixelData(file, matrix, imgWidth, imgHeight, pixelOffset))
//    {
//        cout << "Error: could not read BMP pixel data.\n";
//        file.close();
//        return;
//    }
//    file.close();
//
//    string pattern = scanner.extractPattern(matrix, imgWidth, imgHeight);
//    if (pattern.empty())
//    {
//        cout << "Error: no barcode found in image.\n";
//        return;
//    }
//
//    string number = decoder.decodeSixDigits(pattern);
//    if (number.empty())
//    {
//        cout << "Error: could not decode barcode.\n";
//        return;
//    }
//    cout << "Barcode scanned successfully!\n";
//    cout << "Decoded number: " << number << endl;
//}

void BarcodeSystem::showMenu()
{
    string line;
    int choice = -1;

    while (choice != 0)
    {
        cout << "\n=== Barcode Reader and Scanner ===\n";
        cout << "1. Generate Barcode\n";
        cout << "2. Scan Barcode\n";
        cout << "0. Exit\n";

        cout << "Choice: ";
        getline(cin, line);

        // accept only a single digit character
        if (line.length() != 1 || line[0] < '0' || line[0] > '9') {
            cout << "Invalid choice. Enter 0, 1 or 2.\n";
            continue;
        }
        choice = line[0] - '0';

        if (choice == 1)
        {
            string input;
            cout << "Enter 6-digit number: ";
            getline(cin, input);
            generateBarcode(input);
        }
        /*else if (choice == 2)
        {
            string filename;
            cout << "Enter BMP filename to scan: ";
            getline(cin, filename);
            decodeBarcode(filename);
        }*/
        else if (choice != 0)
        {
            cout << "Invalid choice. Enter 0, 1 or 2.\n";
        }
    }
}
