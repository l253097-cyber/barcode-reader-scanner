#ifndef ORDERFILEHANDLER_H
#define ORDERFILEHANDLER_H

#include "Common/Config.h"
#include <string>
#include "Models/Order.h"

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

class OrderFileHandler {
private:
    std::string fileName;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    explicit OrderFileHandler(const std::string& fileName = std::string(POS_DATA_DIR) + "Order.txt") : fileName(fileName) {}

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool saveOrder(const Order& order) const;   // Member 5
    int loadOrders(Order* outOrders, int maxCount) const;   // Member 5
    bool parseOrderRecord(const std::string& line, Order& outOrder) const;   // Member 4
    std::string serializeOrderRecord(const Order& order) const;   // Member 4
};

#endif // ORDERFILEHANDLER_H
