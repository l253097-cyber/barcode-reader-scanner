#include "FileHandlers/BillFileHandler.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
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
    if (outBills == nullptr || maxCount <= 0)
        return 0;

    std::ifstream file(fileName);                    // CHECK: name of the file path variable
    if (!file.is_open())
        return 0;

    int count = 0;
    std::string line;
    while (count < maxCount && std::getline(file, line))
    {
        Bill bill;
        if (parseBillRecord(line, bill))             // bad or empty lines are skipped
            outBills[count++] = bill;
    }
    return count;
    // ===== MEMBER 3 : END =====
}

bool BillFileHandler::parseBillRecord(const std::string& line, Bill& outBill) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Split by '|' and fill outBill.
    std::string text = line;
    if (!text.empty() && text.back() == '\r')        // line from a file saved on Windows
        text.pop_back();
    if (text.empty())
        return false;

    // split into exactly 12 fields
    const int FIELD_COUNT = 12;
    std::string fields[FIELD_COUNT];
    int found = 0;
    std::string current;
    for (size_t i = 0; i <= text.size(); i++)
    {
        if (i == text.size() || text[i] == '|')
        {
            if (found >= FIELD_COUNT)
                return false;                        // too many fields
            fields[found++] = current;
            current.clear();
        }
        else
            current += text[i];
    }
    if (found != FIELD_COUNT)
        return false;                                // too few fields

    try
    {
        double unitPrice = std::stod(fields[4]);
        double discountPerUnit = std::stod(fields[5]);
        int    quantity = std::stoi(fields[6]);
        double subtotal = std::stod(fields[7]);
        double totalTax = std::stod(fields[8]);
        double totalDiscount = std::stod(fields[9]);
        double payable = std::stod(fields[10]);

        outBill = Bill(fields[0], fields[1], fields[2], fields[3],
            unitPrice, discountPerUnit, quantity,
            subtotal, totalTax, totalDiscount, payable, fields[11]);
    }
    catch (...)                                      // a field that isn't a valid number
    {
        return false;
    }
    return true;
    // ===== MEMBER 3 : END =====
}

std::string BillFileHandler::serializeBillRecord(const Bill& bill) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Join the 12 fields with '|'.
    auto clean = [](std::string s)      // a '|' or newline inside a text field would break the file format
        {
            for (char& c : s)
                if (c == '|' || c == '\n' || c == '\r')
                    c = ' ';
            return s;
        };

    std::ostringstream out;
    out << std::fixed << std::setprecision(2);       // money with 2 decimals
    out << clean(bill.getBillId()) << '|'
        << clean(bill.getCustomerName()) << '|'
        << clean(bill.getOrderId()) << '|'
        << clean(bill.getProductAcronym()) << '|'
        << bill.getUnitPrice() << '|'
        << bill.getDiscountPerUnit() << '|'
        << bill.getQuantity() << '|'
        << bill.getSubtotal() << '|'
        << bill.getTotalTax() << '|'
        << bill.getTotalDiscount() << '|'
        << bill.getPayableAmount() << '|'
        << clean(bill.getPaymentStatus());
    return out.str();
    // ===== MEMBER 3 : END =====
}
