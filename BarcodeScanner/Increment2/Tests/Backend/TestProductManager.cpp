// Unit test for ProductManager (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include <string>
#include "Managers/ProductManager.h"

int main()
{
    // Two products, like two rows of Product.txt
    Product list[2] = {
        Product(1, "100001", "MLK", "Milk", "count", 250.0, 15.0, 5.0, 10, "Data/Barcodes/100001.bmp"),
        Product(2, "100002", "RCE", "Rice", "weight", 300.0, 20.0, 0.0, 4, "Data/Barcodes/100002.bmp")
    };
    ProductManager pm;
    pm.setProducts(list, 2);

    // findProductByBarcode
    Product* found = pm.findProductByBarcode("100002");
    assert(found != nullptr && found->getProductId() == 2);
    assert(pm.findProductByBarcode("999999") == nullptr);
    assert(pm.findProductByBarcode("") == nullptr);

    // findProductById
    found = pm.findProductById(1);
    assert(found != nullptr && found->getBarcode() == "100001");
    assert(pm.findProductById(99) == nullptr);
    assert(pm.findProductById(0) == nullptr);

    // An empty manager must not crash
    ProductManager empty;
    assert(empty.findProductByBarcode("100001") == nullptr);
    assert(empty.findProductById(1) == nullptr);
    assert(empty.getProductDescription("100001") == "Product not found");
    assert(!empty.checkAvailableQuantity(1, 1));
    assert(!empty.deductStock(1, 1));

    // getProductDescription
    std::string text = pm.getProductDescription("100001");
    assert(text.find("Milk") != std::string::npos);
    assert(text.find("250.00") != std::string::npos);
    assert(pm.getProductDescription("999999") == "Product not found");

    // checkAvailableQuantity
    assert(pm.checkAvailableQuantity(1, 10));    // exactly the stock
    assert(!pm.checkAvailableQuantity(1, 11));   // more than the stock
    assert(!pm.checkAvailableQuantity(1, 0));
    assert(!pm.checkAvailableQuantity(1, -1));
    assert(!pm.checkAvailableQuantity(99, 1));   // unknown product

    // deductStock
    assert(pm.deductStock(1, 3));
    assert(pm.findProductById(1)->getAvailableQuantity() == 7);
    assert(!pm.deductStock(1, 8));               // more than is left
    assert(pm.findProductById(1)->getAvailableQuantity() == 7);
    assert(!pm.deductStock(99, 1));
    assert(!pm.deductStock(1, 0));

    // setProducts keeps its own copy, so the source array is untouched
    assert(list[0].getAvailableQuantity() == 10);

    std::cout << "[TestProductManager] all tests passed\n";
    return 0;
}