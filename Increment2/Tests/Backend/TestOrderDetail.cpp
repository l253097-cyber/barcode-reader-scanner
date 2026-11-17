// Unit test for OrderDetail (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include "Models/OrderDetail.h"

int main()
{
    OrderDetail obj;   // object must be constructible

    // a default object starts empty
    assert(obj.getOrderId().empty());
    assert(obj.getProductId() == 0);
    assert(obj.getQuantity() == 0);

    // MEMBER 4: tests for setQuantity()
    OrderDetail d("11111111", 101, "123456", 2);
    assert(d.getOrderId() == "11111111");          // constructor stores the values
    assert(d.getProductId() == 101);
    assert(d.getProductBarcode() == "123456");
    assert(d.getQuantity() == 2);

    d.setQuantity(5);                              // valid change
    assert(d.getQuantity() == 5);

    d.setQuantity(1);                              // smallest valid quantity
    assert(d.getQuantity() == 1);

    d.setQuantity(0);                              // 0 is invalid: old value stays
    assert(d.getQuantity() == 1);

    d.setQuantity(-3);                             // negative is invalid: old value stays
    assert(d.getQuantity() == 1);

    d.setQuantity(1000);                           // a large quantity is fine
    assert(d.getQuantity() == 1000);

    std::cout << "[TestOrderDetail] all tests passed\n";
    return 0;
}