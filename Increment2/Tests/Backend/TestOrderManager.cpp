// Unit test for OrderManager (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include "Managers/OrderManager.h"

int main()
{
    OrderManager obj;   // object must be constructible
    (void)obj;

    // MEMBER 2: write tests for createOrder(), addProductToOrder(), removeProductFromOrder(), updateProductQuantity(), calculateOrderSubtotal(), validateOrder()
    // Example: assert(obj.someFunction(...) == expectedValue);

    std::cout << "[TestOrderManager] skeleton OK - add real tests\n";
    return 0;
}
