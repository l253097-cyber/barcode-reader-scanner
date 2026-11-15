#include "Managers/OrderDetailManager.h"

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

bool OrderDetailManager::addOrderDetail(const OrderDetail& detail)
{
    // ===== MEMBER 4 : START =====
    // TODO: Append to details[] if there is space.
    return false;
    // ===== MEMBER 4 : END =====
}

int OrderDetailManager::getOrderDetails(const std::string& orderId, OrderDetail* outArray, int maxCount) const
{
    // ===== MEMBER 4 : START =====
    // TODO: Copy all details of this orderId into outArray (max maxCount). Return how many were copied.
    return 0;
    // ===== MEMBER 4 : END =====
}

OrderDetail* OrderDetailManager::findOrderDetail(const std::string& orderId, int productId)
{
    // ===== MEMBER 4 : START =====
    // TODO: Return pointer to matching detail or nullptr.
    return nullptr;
    // ===== MEMBER 4 : END =====
}

bool OrderDetailManager::updateOrderDetailQuantity(const std::string& orderId, int productId, int newQuantity)
{
    // ===== MEMBER 4 : START =====
    // TODO: Find detail and call setQuantity().
    return false;
    // ===== MEMBER 4 : END =====
}

bool OrderDetailManager::removeOrderDetail(const std::string& orderId, int productId)
{
    // ===== MEMBER 4 : START =====
    // TODO: Remove the record and shift the rest left.
    return false;
    // ===== MEMBER 4 : END =====
}
