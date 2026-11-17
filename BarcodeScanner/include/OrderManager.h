#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "Models/Order.h"
#include "Models/OrderDetail.h"
#include "Models/Product.h"
#include "Managers/ProductManager.h"
#include <string>

/*
 * ============================================================
 *  OrderManager
 *  Builds the current order and its items (add / remove / change quantity / validate).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 2 : createOrder(), addProductToOrder(), removeProductFromOrder(), updateProductQuantity(), calculateOrderSubtotal(), validateOrder()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class OrderManager {
private:
    Order currentOrder;
    OrderDetail* orderDetails = nullptr;
    int detailCount = 0;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    static const int MAX_ITEMS = 50;
    OrderManager() { orderDetails = new OrderDetail[MAX_ITEMS]; }
    ~OrderManager() { delete[] orderDetails; }
    OrderManager(const OrderManager&) = delete;
    OrderManager& operator=(const OrderManager&) = delete;
    Order& getCurrentOrder() { return currentOrder; }
    const OrderDetail* getOrderDetails() const { return orderDetails; }
    int getDetailCount() const { return detailCount; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool createOrder(const std::string& customerName, const std::string& customerContact);   // Member 2
    bool addProductToOrder(const Product& product, int quantity);   // Member 2
    bool removeProductFromOrder(int productId);   // Member 2
    bool updateProductQuantity(int productId, int newQuantity);   // Member 2
    double calculateOrderSubtotal(const ProductManager& productManager) const;   // Member 2
    bool validateOrder(const ProductManager& productManager) const;   // Member 2
};

#endif // ORDERMANAGER_H
