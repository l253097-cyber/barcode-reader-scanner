#ifndef ORDERDETAILFILEHANDLER_H
#define ORDERDETAILFILEHANDLER_H

#include "Common/Config.h"
#include <string>
#include "Models/OrderDetail.h"

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

class OrderDetailFileHandler {
private:
    std::string fileName;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    explicit OrderDetailFileHandler(const std::string& fileName = std::string(POS_DATA_DIR) + "OrderDetail.txt") : fileName(fileName) {}

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool saveOrderDetails(const OrderDetail* items, int count) const;   // Member 5
    int loadOrderDetails(OrderDetail* outItems, int maxCount) const;   // Member 2
    bool parseOrderDetailRecord(const std::string& line, OrderDetail& outItem) const;   // Member 2
    std::string serializeOrderDetailRecord(const OrderDetail& item) const;   // Member 2
};

#endif // ORDERDETAILFILEHANDLER_H
