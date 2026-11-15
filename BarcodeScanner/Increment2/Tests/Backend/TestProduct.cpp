// Unit test for Product (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include "Models/Product.h"

static Product makeProduct(int stock)
{
    return Product(1, "100001", "MLK", "Milk", "count", 250.0, 15.0, 5.0, stock,
        "Data/Barcodes/100001.bmp");
}

int main()
{
    Product p = makeProduct(10);
    assert(p.updateStock(3));
    assert(p.getAvailableQuantity() == 7);

    assert(p.updateStock(7));                 // selling everything is allowed
    assert(p.getAvailableQuantity() == 0);

    p = makeProduct(10);
    assert(!p.updateStock(11));               // more than available
    assert(p.getAvailableQuantity() == 10);   // unchanged
    assert(!p.updateStock(0));
    assert(!p.updateStock(-2));
    assert(p.getAvailableQuantity() == 10);

    std::cout << "[TestProduct] all tests passed\n";
    return 0;
}