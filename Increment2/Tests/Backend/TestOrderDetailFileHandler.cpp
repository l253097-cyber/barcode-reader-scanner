// Test for OrderDetailFileHandler (Member 2 functions)
#include <iostream>
#include <fstream>
#include <string>
#include "FileHandlers/OrderDetailFileHandler.h"

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
    // Ek temporary file banao
    std::ofstream out("test_orderdetail.txt");
    out << "ORD1|1|111|2" << std::endl;
    out << "ORD1|2|222|5" << std::endl;
    out << "bad line" << std::endl;
    out << std::endl;
    out.close();

    OrderDetailFileHandler handler("test_orderdetail.txt");
    OrderDetail items[10];
    OrderDetail item;

    // ----- tests for serializeOrderDetailRecord -----
    OrderDetail d("ORD5", 4, "444", 9);
    check(handler.serializeOrderDetailRecord(d) == "ORD5|4|444|9", "serialize gives correct line");

    // ----- tests for parseOrderDetailRecord -----
    check(handler.parseOrderDetailRecord("ORD9|3|333|7", item) == true, "good line parses");
    check(item.getOrderId() == "ORD9", "parsed orderId");
    check(item.getProductId() == 3, "parsed productId");
    check(item.getProductBarcode() == "333", "parsed barcode");
    check(item.getQuantity() == 7, "parsed quantity");
    check(handler.parseOrderDetailRecord("a|b", item) == false, "too few fields fails");
    check(handler.parseOrderDetailRecord("ORD9|x|333|7", item) == false, "productId not a number fails");
    check(handler.parseOrderDetailRecord("ORD9|3|333", item) == false, "3 fields fails");
    check(handler.parseOrderDetailRecord("ORD9|3|333|7|8", item) == false, "5 fields fails");
    check(handler.parseOrderDetailRecord("ORD9|3|333|0", item) == false, "quantity 0 fails");

    // ----- tests for loadOrderDetails -----
    int count = handler.loadOrderDetails(items, 10);
    check(count == 2, "2 good lines loaded (bad and empty lines skipped)");
    check(items[0].getOrderId() == "ORD1", "first item orderId");
    check(items[0].getProductId() == 1, "first item productId");
    check(items[0].getQuantity() == 2, "first item quantity");
    check(items[1].getQuantity() == 5, "second item quantity");
    check(handler.loadOrderDetails(items, 1) == 1, "maxCount 1 loads only 1");

    OrderDetailFileHandler missing("no_such_file.txt");
    check(missing.loadOrderDetails(items, 10) == 0, "missing file gives 0");

    std::cout << "Failed tests: " << failed << std::endl;
    return failed;
}