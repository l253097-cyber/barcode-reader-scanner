#include "FileHandlers/BillFileHandler.h"

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

bool BillFileHandler::saveBill(const Bill& bill) const
{
    // ===== MEMBER 5 : START =====
    // TODO: Append serializeBillRecord(bill) to the file.
    return false;
    // ===== MEMBER 5 : END =====
}

int BillFileHandler::loadBills(Bill* outBills, int maxCount) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Read file, parseBillRecord() each line, return count.
    return 0;
    // ===== MEMBER 3 : END =====
}

bool BillFileHandler::parseBillRecord(const std::string& line, Bill& outBill) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Split by '|' and fill outBill.
    return false;
    // ===== MEMBER 3 : END =====
}

std::string BillFileHandler::serializeBillRecord(const Bill& bill) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Join the 12 fields with '|'.
    return "";
    // ===== MEMBER 3 : END =====
}
