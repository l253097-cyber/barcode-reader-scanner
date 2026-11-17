// Unit test for PaymentManager (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include "Managers/PaymentManager.h"

int main()
{
    PaymentManager pay;

    // validatePayment(amount, payableAmount, mode, merchant)
    assert(pay.validatePayment(1000, 990, "Cash", "") == true);        // more than enough
    assert(pay.validatePayment(990, 990, "Cash", "") == true);         // exact amount
    assert(pay.validatePayment(1000, 990, "Card", "Visa") == true);
    assert(pay.validatePayment(1000, 990, "Wallet", "Easypaisa") == true);
    assert(pay.validatePayment(500, 990, "Cash", "") == false);        // not enough money
    assert(pay.validatePayment(0, 0, "Cash", "") == false);            // zero amount
    assert(pay.validatePayment(-5, 990, "Cash", "") == false);         // negative amount
    assert(pay.validatePayment(1000, 990, "Bitcoin", "") == false);    // unknown mode
    assert(pay.validatePayment(1000, 990, "", "") == false);           // empty mode

    // processPayment
    assert(pay.processPayment(500, 990, "Cash", "") == false);         // rejected
    assert(pay.processPayment(1000, 990, "Cash", "") == true);         // accepted

    // updateOrderPaymentStatus after an accepted payment: the bill becomes Paid
    Order order;
    Bill bill;
    bill.setPaymentStatus("Unpaid");
    pay.updateOrderPaymentStatus(order, bill);
    assert(bill.getPaymentStatus() == "Paid");

    // after a rejected payment nothing was paid, so the bill stays Unpaid
    PaymentManager fresh;
    Order order2;
    Bill bill2;
    bill2.setPaymentStatus("Unpaid");
    fresh.processPayment(500, 990, "Cash", "");                        // rejected
    fresh.updateOrderPaymentStatus(order2, bill2);
    assert(bill2.getPaymentStatus() == "Unpaid");

    // Optional: these two only work once Member 2 has written Order::setPaymentDetails / setOrderStatus
    // assert(order.getPaymentAmount() == 1000);
    // assert(order.getPaymentMode() == "Cash");

    std::cout << "PaymentManager OK\n";

    // MEMBER 3: write tests for validatePayment(), processPayment(), updateOrderPaymentStatus()
    // Example: assert(obj.someFunction(...) == expectedValue);

    std::cout << "[TestPaymentManager] skeleton OK - add real tests\n";
    return 0;
}
