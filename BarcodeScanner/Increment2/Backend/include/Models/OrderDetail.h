#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include <string>

/*
 * ============================================================
 *  OrderDetail
 *  Data class: one product line of an order (OrderDetail.txt).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 4 : setQuantity()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class OrderDetail {
private:
    std::string orderId;
    int productId = 0;
    std::string productBarcode;
    int quantity = 0;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    OrderDetail() = default;
    OrderDetail(const std::string& orderId, int productId, const std::string& productBarcode, int quantity) : orderId(orderId), productId(productId), productBarcode(productBarcode), quantity(quantity) {}
    const std::string& getOrderId() const { return orderId; }
    int getProductId() const { return productId; }
    const std::string& getProductBarcode() const { return productBarcode; }
    int getQuantity() const { return quantity; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    void setQuantity(int newQuantity);   // Member 4
};

#endif // ORDERDETAIL_H
