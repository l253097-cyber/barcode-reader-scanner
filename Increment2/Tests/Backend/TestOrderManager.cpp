// Test for OrderManager (Member 2 functions)
#include <iostream>
#include <string>
#include "Managers/OrderManager.h"

int failed = 0;

void check(bool condition, const std::string& testName)
{
    if (condition)
    {
        std::cout << "PASS: " << testName << std::endl;
    }
    else
    {
        std::cout << "FAIL: " << testName << std::endl;
        failed++;
    }
}

int main()
{
    // Do products banao
    Product list[2];
    list[0] = Product(1, "111", "MLK", "Milk", "Litre", 250.0, 5.0, 10.0, 50, "a.bmp");
    list[1] = Product(2, "222", "BRD", "Bread", "Piece", 120.0, 0.0, 0.0, 30, "b.bmp");
    ProductManager pm;
    pm.setProducts(list, 2);

    OrderManager om;

    // ----- tests for createOrder -----
    check(om.createOrder("", "0300") == false, "empty customer name is rejected");
    check(om.createOrder("Ali", "0300") == true, "order created");
    check(om.getCurrentOrder().getCustomerName() == "Ali", "customer name saved");
    check(om.getCurrentOrder().getOrderStatus() == "Pending", "status is Pending");
    check(om.getDetailCount() == 0, "new order has no items");

    // ----- tests for addProductToOrder -----
    check(om.addProductToOrder(list[0], 2) == true, "add Milk x2");
    check(om.getDetailCount() == 1, "1 item in order");
    check(om.addProductToOrder(list[0], 3) == true, "add Milk x3 more");
    check(om.getDetailCount() == 1, "still 1 item (merged)");
    check(om.getOrderDetails()[0].getQuantity() == 5, "Milk quantity is 5");
    check(om.addProductToOrder(list[1], 0) == false, "quantity 0 is rejected");
    check(om.addProductToOrder(list[1], 1) == true, "add Bread x1");
    check(om.getDetailCount() == 2, "2 items in order");

    // ----- tests for updateProductQuantity -----
    check(om.updateProductQuantity(1, 2) == true, "Milk quantity set to 2");
    check(om.getOrderDetails()[0].getQuantity() == 2, "Milk quantity is 2");
    check(om.updateProductQuantity(1, 0) == false, "quantity 0 is rejected");
    check(om.updateProductQuantity(99, 2) == false, "unknown product rejected");

    // ----- tests for calculateOrderSubtotal -----
    // Milk 2 x 250 = 500, Bread 1 x 120 = 120, total 620
    check(om.calculateOrderSubtotal(pm) == 620.0, "subtotal is 620");

    // ----- tests for validateOrder -----
    check(om.validateOrder(pm) == true, "valid order passes");
    om.updateProductQuantity(1, 100);
    check(om.validateOrder(pm) == false, "quantity more than stock fails");
    om.updateProductQuantity(1, 2);

    // ----- tests for removeProductFromOrder -----
    check(om.removeProductFromOrder(2) == true, "remove Bread");
    check(om.getDetailCount() == 1, "1 item left");
    check(om.removeProductFromOrder(99) == false, "remove unknown product fails");

    // Khali order invalid hona chahiye
    om.createOrder("Sara", "0311");
    check(om.validateOrder(pm) == false, "empty order is invalid");

    std::cout << "Failed tests: " << failed << std::endl;
    return failed;
}