// Unit test for BillFileHandler (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include "FileHandlers/BillFileHandler.h"

int main()
{
    BillFileHandler handler;   // CHECK: if the constructor needs a path, pass one here

    // CHECK: parameter order of the Bill constructor (see Bill.h line 36)
    Bill bill("B1", "Ali", "ORD1", "A", 500.0, 50.0, 2, 1000.0, 90.0, 100.0, 990.0, "Unpaid");

    // ---- serializeBillRecord: 12 fields joined with '|' ----
    std::string line = handler.serializeBillRecord(bill);
    assert(line == "B1|Ali|ORD1|A|500.00|50.00|2|1000.00|90.00|100.00|990.00|Unpaid");

    // ---- parseBillRecord: the line turns back into the same bill ----
    Bill back;
    assert(handler.parseBillRecord(line, back) == true);
    assert(back.getBillId() == "B1");
    assert(back.getCustomerName() == "Ali");
    assert(back.getOrderId() == "ORD1");
    assert(back.getQuantity() == 2);
    assert(back.getPayableAmount() == 990.0);
    assert(back.getPaymentStatus() == "Unpaid");

    // ---- parseBillRecord: bad lines are rejected ----
    Bill junk;
    assert(handler.parseBillRecord("", junk) == false);                  // empty line
    assert(handler.parseBillRecord("B1|Ali|ORD1", junk) == false);       // too few fields
    assert(handler.parseBillRecord(line + "|extra", junk) == false);     // too many fields
    assert(handler.parseBillRecord("B1|Ali|ORD1|A|abc|50.00|2|1000.00|90.00|100.00|990.00|Unpaid", junk) == false);   // not a number

#ifdef WITH_FILE
    // ---- loadBills: 2 good lines and 1 bad line in a temporary file ----
    {
        std::ofstream out("bills_test.txt");
        out << line << "\n" << "garbage line\n" << line << "\n";
    }
    BillFileHandler fileHandler("bills_test.txt");   // CHECK: the real way to give the handler a path
    Bill loaded[5];
    int n = fileHandler.loadBills(loaded, 5);
    assert(n == 2);                                  // the bad line is skipped
    assert(loaded[0].getBillId() == "B1");
    assert(fileHandler.loadBills(loaded, 1) == 1);   // never more than maxCount
    std::remove("bills_test.txt");
#endif

    std::cout << "BillFileHandler OK\n";
    // MEMBER 3: write tests for loadBills(), parseBillRecord(), serializeBillRecord()
    // MEMBER 5: write tests for saveBill()
    // Example: assert(obj.someFunction(...) == expectedValue);

    std::cout << "[TestBillFileHandler] skeleton OK - add real tests\n";
    return 0;
}
