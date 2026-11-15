// Test for Order (Member 2: setOrderStatus, setPaymentDetails)
#include <iostream>
#include <string>
#include "Models/Order.h"

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
    Order o("ORD1", "2026-01-01", "10:00:00", "Ali", "0300", "Pending", 0.0, "", "");

    // ----- tests for setOrderStatus -----
    o.setOrderStatus("Paid");
    check(o.getOrderStatus() == "Paid", "status changes to Paid");
    o.setOrderStatus("");
    check(o.getOrderStatus() == "Paid", "empty status is ignored");

    // ----- tests for setPaymentDetails -----
    o.setPaymentDetails(500.0, "card", "Visa");
    check(o.getPaymentAmount() == 500.0, "payment amount saved");
    check(o.getPaymentMode() == "card", "payment mode saved");
    check(o.getPaymentMerchant() == "Visa", "merchant saved");
    o.setPaymentDetails(-10.0, "cash", "X");
    check(o.getPaymentAmount() == 500.0, "negative amount is ignored");

    std::cout << "Failed tests: " << failed << std::endl;
    return failed;
}