#ifndef BILLFILEHANDLER_H
#define BILLFILEHANDLER_H

#include "Common/Config.h"
#include <string>
#include "Models/Bill.h"

/*
 * ============================================================
 *  BillFileHandler
 *  Reads/writes Bill.txt. Record format (one per line, '|' separated): billId|customerName|orderId|productAcronym|unitPrice|discountPerUnit|quantity|subtotal|totalTax|totalDiscount|payableAmount|paymentStatus
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 3 : loadBills(), parseBillRecord(), serializeBillRecord()
 *    Member 5 : saveBill()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class BillFileHandler {
private:
    std::string fileName;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    explicit BillFileHandler(const std::string& fileName = std::string(POS_DATA_DIR) + "Bill.txt") : fileName(fileName) {}

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool saveBill(const Bill& bill) const;   // Member 5
    int loadBills(Bill* outBills, int maxCount) const;   // Member 3
    bool parseBillRecord(const std::string& line, Bill& outBill) const;   // Member 3
    std::string serializeBillRecord(const Bill& bill) const;   // Member 3
};

#endif // BILLFILEHANDLER_H
