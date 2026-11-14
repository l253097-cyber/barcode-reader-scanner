// Unit test for BillFileHandler (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include "FileHandlers/BillFileHandler.h"

int main()
{
    BillFileHandler obj;   // object must be constructible
    (void)obj;

    // MEMBER 3: write tests for loadBills(), parseBillRecord(), serializeBillRecord()
    // MEMBER 5: write tests for saveBill()
    // Example: assert(obj.someFunction(...) == expectedValue);

    std::cout << "[TestBillFileHandler] skeleton OK - add real tests\n";
    return 0;
}
