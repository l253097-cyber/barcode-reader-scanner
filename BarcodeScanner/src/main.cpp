
#include <iostream>
using namespace std;
#include <iostream>
#include <string>
#include "BarcodeSystem.h"
#include "BarcodeEncoder.h"
using namespace std;

int main()
{
    if (!BarcodeEncoder::verifyPattern())
    {
        cout << "Fatal error: barcode pattern table is invalid.\n";
        return 1;                      // stop the program
    }

    BarcodeSystem system;

    system.showMenu();
   
}

///*
// * File    : main.cpp
// * Purpose : Console entry point (Member 5 will integrate the full workflow)
// */
//#include <iostream>
//
// // Test runners (defined in tests/TestMemberN.cpp)
//void runMember1Tests();
//void runMember2Tests();
//void runMember3Tests();
//void runMember4Tests();
//void runMember5Tests();
//
//int main()
//{
//    std::cout << "=== Barcode Reader and Scanner ===\n";
//
//    // TODO (Member 5): menu + generate/scan workflow.
//    // For now, just run all tests:
//    runMember1Tests();
//    runMember2Tests();
//    runMember3Tests();
 //  runMember4Tests();
//    runMember5Tests();
//    return 0;
//}