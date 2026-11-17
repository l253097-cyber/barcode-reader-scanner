#include "FileHandlers/OrderFileHandler.h"
#include <cstdlib>
#include <iomanip>
#include <sstream>
/*
 * ============================================================
 *  OrderFileHandler
 *  Reads/writes Order.txt. Record format (one per line, '|' separated): orderId|date|time|customerName|customerContact|status|paymentAmount|paymentMode|paymentMerchant
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 4 : parseOrderRecord(), serializeOrderRecord()
 *    Member 5 : saveOrder(), loadOrders()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

bool OrderFileHandler::saveOrder(const Order& order) const
{
    // ===== MEMBER 5 : START =====
    // TODO: Append serializeOrderRecord(order) as a new line (or replace the line with the same orderId).
    return false;
    // ===== MEMBER 5 : END =====
}

int OrderFileHandler::loadOrders(Order* outOrders, int maxCount) const
{
    // ===== MEMBER 5 : START =====
    // TODO: Read every line, parseOrderRecord(), return how many orders were loaded.
    return 0;
    // ===== MEMBER 5 : END =====
}

bool OrderFileHandler::parseOrderRecord(const std::string& line, Order& outOrder) const
{
    // ===== MEMBER 4 : START =====
    const char sep = '|';          // field separator (same char as in serializeOrderRecord)
    const int FIELD_COUNT = 9;

    // Windows line endings: drop a trailing \r or \n
    std::string text = line;
    while (!text.empty() && (text.back() == '\r' || text.back() == '\n'))
        text.pop_back();
    if (text.empty())
        return false;

    // Split by sep. Empty fields (e.g. unpaid order: no mode/merchant) must be kept.
    std::string fields[FIELD_COUNT];
    int count = 0;
    size_t start = 0;
    while (true)
    {
        if (count >= FIELD_COUNT)              // more than 9 fields
            return false;
        size_t pos = text.find(sep, start);
        if (pos == std::string::npos)
        {
            fields[count++] = text.substr(start);   // last field
            break;
        }
        fields[count++] = text.substr(start, pos - start);
        start = pos + 1;
    }
    if (count != FIELD_COUNT)                  // fewer than 9 fields
        return false;

    if (fields[0].empty())                     // an order must have an id
        return false;

    // paymentAmount must be a valid non-negative number
    char* end = nullptr;
    double amount = std::strtod(fields[6].c_str(), &end);
    if (fields[6].empty() || *end != '\0' || amount < 0.0)
        return false;

    // outOrder is only changed when everything above was valid
    outOrder = Order(fields[0], fields[1], fields[2], fields[3], fields[4],
        fields[5], amount, fields[7], fields[8]);
    return true;
    // ===== MEMBER 4 : END =====
}

std::string OrderFileHandler::serializeOrderRecord(const Order& order) const
{
    // ===== MEMBER 4 : START =====
    const char sep = '|';

    // A separator or newline inside a text field would break the line, so replace it by a space
    auto clean = [sep](std::string s) {
        for (char& c : s)
            if (c == sep || c == '\n' || c == '\r')
                c = ' ';
        return s;
        };

    std::ostringstream out;
    out << clean(order.getOrderId()) << sep
        << clean(order.getOrderDate()) << sep
        << clean(order.getOrderTime()) << sep
        << clean(order.getCustomerName()) << sep
        << clean(order.getCustomerContact()) << sep
        << clean(order.getOrderStatus()) << sep
        << std::fixed << std::setprecision(2) << order.getPaymentAmount() << sep
        << clean(order.getPaymentMode()) << sep
        << clean(order.getPaymentMerchant());
    return out.str();
    // ===== MEMBER 4 : END =====
}