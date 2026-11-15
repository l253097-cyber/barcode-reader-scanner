// Unit test for BillManager (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include "Managers/BillManager.h"

int main()
{
    BillManager obj;   // object must be constructible
   
    assert(obj.calculatePayableAmount(1000, 90, 100) == 990);   // 1000 - 100 + 90
    assert(obj.calculatePayableAmount(100, 0, 150) == 0);       // never below zero
    std::cout << "BillManager OK\n";
    // MEMBER 3: write tests for calculateSubtotal(), calculateTotalDiscount(), calculateTotalTax(), calculatePayableAmount(), generateBill()
    // Example: assert(obj.someFunction(...) == expectedValue);

    std::cout << "[TestBillManager] skeleton OK - add real tests\n";
    return 0;
}
