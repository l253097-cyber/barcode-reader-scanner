#include "FileHandlers/OrderFileHandler.h"

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
    // TODO: Split by '|' and build outOrder. (Assigned to Member 4 - not in Part 3 list, see README.)
    return false;
    // ===== MEMBER 4 : END =====
}

std::string OrderFileHandler::serializeOrderRecord(const Order& order) const
{
    // ===== MEMBER 4 : START =====
    // TODO: Join the 9 fields with '|'. (Member 4)
    return "";
    // ===== MEMBER 4 : END =====
}
