#include "Managers/OrderManager.h"

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

bool OrderManager::createOrder(const std::string& customerName, const std::string& customerContact)
{
    // ===== MEMBER 2 : START =====
    // TODO: Reset detailCount to 0, generate orderId, set date/time (use <ctime>), status "Pending", then build currentOrder.
    return false;
    // ===== MEMBER 2 : END =====
}

bool OrderManager::addProductToOrder(const Product& product, int quantity)
{
    // ===== MEMBER 2 : START =====
    // TODO: If product already in orderDetails[], add to its quantity; else append a new OrderDetail (max MAX_ITEMS).
    return false;
    // ===== MEMBER 2 : END =====
}

bool OrderManager::removeProductFromOrder(int productId)
{
    // ===== MEMBER 2 : START =====
    // TODO: Find the item, shift remaining items left, detailCount--.
    return false;
    // ===== MEMBER 2 : END =====
}

bool OrderManager::updateProductQuantity(int productId, int newQuantity)
{
    // ===== MEMBER 2 : START =====
    // TODO: Find the item and call setQuantity(newQuantity).
    return false;
    // ===== MEMBER 2 : END =====
}

double OrderManager::calculateOrderSubtotal(const ProductManager& productManager) const
{
    // ===== MEMBER 2 : START =====
    // TODO: Sum of (unitPrice * quantity) for every item. Use productManager to get the price by productId.
    return 0.0;
    // ===== MEMBER 2 : END =====
}

bool OrderManager::validateOrder(const ProductManager& productManager) const
{
    // ===== MEMBER 2 : START =====
    // TODO: Return false if order is empty, customer name is empty, or any item quantity is more than stock.
    return false;
    // ===== MEMBER 2 : END =====
}
