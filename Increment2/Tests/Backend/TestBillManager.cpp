// Unit test for BillManager (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include "Managers/BillManager.h"

int main()
{
    BillManager obj;   // object must be constructible
    (void)obj;

    // MEMBER 3: write tests for calculateSubtotal(), calculateTotalDiscount(), calculateTotalTax(), calculatePayableAmount(), generateBill()
    // Example: assert(obj.someFunction(...) == expectedValue);

    std::cout << "[TestBillManager] skeleton OK - add real tests\n";
    return 0;
}
