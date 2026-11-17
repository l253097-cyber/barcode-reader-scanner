// Unit test for OrderFileHandler (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include <cmath>
#include "FileHandlers/OrderFileHandler.h"

static bool sameOrder(const Order& a, const Order& b)
{
    return a.getOrderId() == b.getOrderId() && a.getOrderDate() == b.getOrderDate()
        && a.getOrderTime() == b.getOrderTime() && a.getCustomerName() == b.getCustomerName()
        && a.getCustomerContact() == b.getCustomerContact() && a.getOrderStatus() == b.getOrderStatus()
        && std::fabs(a.getPaymentAmount() - b.getPaymentAmount()) < 0.001
        && a.getPaymentMode() == b.getPaymentMode() && a.getPaymentMerchant() == b.getPaymentMerchant();
}

int main()
{
    OrderFileHandler obj;   // object must be constructible

    // ---------- serializeOrderRecord ----------
    Order paid("ORD001", "2026-11-17", "14:30:00", "Ali", "03001234567", "Paid", 1250.5, "Card", "Visa");
    assert(obj.serializeOrderRecord(paid) ==
        "ORD001|2026-11-17|14:30:00|Ali|03001234567|Paid|1250.50|Card|Visa");

    Order unpaid("ORD002", "2026-11-17", "15:00:00", "Sara", "0300", "Pending", 0.0, "", "");
    assert(obj.serializeOrderRecord(unpaid) ==
        "ORD002|2026-11-17|15:00:00|Sara|0300|Pending|0.00||");   // empty mode/merchant kept

    Order bad("ORD003", "2026-11-17", "16:00:00", "Ali|Khan", "0300", "Pending", 0.0, "", "");
    assert(obj.serializeOrderRecord(bad) ==
        "ORD003|2026-11-17|16:00:00|Ali Khan|0300|Pending|0.00||"); // '|' inside a name is replaced

    // ---------- parseOrderRecord: valid lines ----------
    Order out;
    assert(obj.parseOrderRecord("ORD001|2026-11-17|14:30:00|Ali|03001234567|Paid|1250.50|Card|Visa", out));
    assert(out.getOrderId() == "ORD001");
    assert(out.getOrderDate() == "2026-11-17");
    assert(out.getOrderTime() == "14:30:00");
    assert(out.getCustomerName() == "Ali");
    assert(out.getCustomerContact() == "03001234567");
    assert(out.getOrderStatus() == "Paid");
    assert(std::fabs(out.getPaymentAmount() - 1250.5) < 0.001);
    assert(out.getPaymentMode() == "Card");
    assert(out.getPaymentMerchant() == "Visa");

    Order out2;
    assert(obj.parseOrderRecord("ORD002|2026-11-17|15:00:00|Sara|0300|Pending|0.00||", out2));
    assert(out2.getOrderStatus() == "Pending");
    assert(out2.getPaymentMode().empty());       // empty fields are kept as empty
    assert(out2.getPaymentMerchant().empty());

    Order out3;
    assert(obj.parseOrderRecord("ORD001|2026-11-17|14:30:00|Ali|03001234567|Paid|1250.50|Card|Visa\r\n", out3));
    assert(out3.getPaymentMerchant() == "Visa"); // trailing \r\n from a Windows file is ignored

    // ---------- round trip: serialize then parse gives the same order ----------
    Order back;
    assert(obj.parseOrderRecord(obj.serializeOrderRecord(paid), back));
    assert(sameOrder(paid, back));
    assert(obj.parseOrderRecord(obj.serializeOrderRecord(unpaid), back));
    assert(sameOrder(unpaid, back));

    // ---------- parseOrderRecord: invalid lines return false ----------
    Order keep("KEEP", "d", "t", "n", "c", "s", 5.0, "m", "x");
    assert(!obj.parseOrderRecord("", keep));                                         // empty line
    assert(!obj.parseOrderRecord("ORD001|2026-11-17|14:30:00", keep));               // too few fields
    assert(!obj.parseOrderRecord("ORD001|d|t|n|c|Paid|1.00|Card|Visa|extra", keep)); // too many fields
    assert(!obj.parseOrderRecord("|d|t|n|c|Paid|1.00|Card|Visa", keep));             // empty order id
    assert(!obj.parseOrderRecord("ORD001|d|t|n|c|Paid|abc|Card|Visa", keep));        // amount not a number
    assert(!obj.parseOrderRecord("ORD001|d|t|n|c|Paid|12x|Card|Visa", keep));        // amount has extra letters
    assert(!obj.parseOrderRecord("ORD001|d|t|n|c|Paid||Card|Visa", keep));           // amount empty
    assert(!obj.parseOrderRecord("ORD001|d|t|n|c|Paid|-5.00|Card|Visa", keep));      // negative amount

    // a failed parse must not change the order that was passed in
    assert(keep.getOrderId() == "KEEP");
    assert(std::fabs(keep.getPaymentAmount() - 5.0) < 0.001);

    // MEMBER 5: write tests for saveOrder(), loadOrders()

    std::cout << "[TestOrderFileHandler] all Member 4 checks passed\n";
    return 0;
}