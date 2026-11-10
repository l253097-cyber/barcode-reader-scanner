#include<iostream>
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

    // temporary: print it to check the encoder
    cout << "Encoded pattern (" << pattern.length() << " modules):\n"
        << pattern << "\n";

}
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
        else if (choice == 2)
        {
            cout << "Scan Barcode is not integrated yet.\n";   // system.scanBarcode()
        }
        else if (choice != 0)
        {
            cout << "Invalid choice. Enter 0, 1 or 2.\n";
        }
    }
}
