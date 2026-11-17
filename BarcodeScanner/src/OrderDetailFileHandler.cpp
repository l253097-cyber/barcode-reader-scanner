#include "FileHandlers/OrderDetailFileHandler.h"

/*
 * ============================================================
 *  OrderDetailFileHandler
 *  Reads/writes OrderDetail.txt. Record format (one per line, '|' separated): orderId|productId|productBarcode|quantity
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 2 : loadOrderDetails(), parseOrderDetailRecord(), serializeOrderDetailRecord()
 *    Member 5 : saveOrderDetails()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

bool OrderDetailFileHandler::saveOrderDetails(const OrderDetail* items, int count) const
{
    // ===== MEMBER 5 : START =====
    // TODO: Append every item using serializeOrderDetailRecord().
    return false;
    // ===== MEMBER 5 : END =====
}

int OrderDetailFileHandler::loadOrderDetails(OrderDetail* outItems, int maxCount) const
{
    // ===== MEMBER 2 : START =====
    // TODO: Read file, parseOrderDetailRecord() each line, return count.
    return 0;
    // ===== MEMBER 2 : END =====
}

bool OrderDetailFileHandler::parseOrderDetailRecord(const std::string& line, OrderDetail& outItem) const
{
    // ===== MEMBER 2 : START =====
    // TODO: Split by '|' and fill outItem.
    return false;
    // ===== MEMBER 2 : END =====
}

std::string OrderDetailFileHandler::serializeOrderDetailRecord(const OrderDetail& item) const
{
    // ===== MEMBER 2 : START =====
    // TODO: Join the 4 fields with '|'.
    return "";
    // ===== MEMBER 2 : END =====
}
