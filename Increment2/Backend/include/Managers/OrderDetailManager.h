#ifndef ORDERDETAILMANAGER_H
#define ORDERDETAILMANAGER_H

#include "Models/OrderDetail.h"
#include <string>

/*
 * ============================================================
 *  OrderDetailManager
 *  Manages the list of all order-detail records (load/search/update/remove).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 4 : addOrderDetail(), getOrderDetails(), findOrderDetail(), updateOrderDetailQuantity(), removeOrderDetail()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class OrderDetailManager {
private:
    OrderDetail* details = nullptr;
    int detailCount = 0;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    static const int MAX_DETAILS = 500;
    OrderDetailManager() { details = new OrderDetail[MAX_DETAILS]; }
    ~OrderDetailManager() { delete[] details; }
    OrderDetailManager(const OrderDetailManager&) = delete;
    OrderDetailManager& operator=(const OrderDetailManager&) = delete;
    int getDetailCount() const { return detailCount; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool addOrderDetail(const OrderDetail& detail);   // Member 4
    int getOrderDetails(const std::string& orderId, OrderDetail* outArray, int maxCount) const;   // Member 4
    OrderDetail* findOrderDetail(const std::string& orderId, int productId);   // Member 4
    bool updateOrderDetailQuantity(const std::string& orderId, int productId, int newQuantity);   // Member 4
    bool removeOrderDetail(const std::string& orderId, int productId);   // Member 4
};

#endif // ORDERDETAILMANAGER_H
