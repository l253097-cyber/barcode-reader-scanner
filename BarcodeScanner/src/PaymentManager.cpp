#include "Managers/PaymentManager.h"

/*
 * ============================================================
 *  PaymentManager
 *  Validates and processes payment (cash / card / wallet).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 3 : validatePayment(), processPayment(), updateOrderPaymentStatus()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

bool PaymentManager::validatePayment(double amount, double payableAmount, const std::string& mode, const std::string& merchant) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Mode must be cash/card/wallet. amount must be >= payableAmount. Merchant required for card/wallet. (OCP tip: keep the list of modes in ONE place.)
    return false;
    // ===== MEMBER 3 : END =====
}

bool PaymentManager::processPayment(double amount, double payableAmount, const std::string& mode, const std::string& merchant)
{
    // ===== MEMBER 3 : START =====
    // TODO: Call validatePayment(); if OK store values in the data members and return true.
    return false;
    // ===== MEMBER 3 : END =====
}

void PaymentManager::updateOrderPaymentStatus(Order& order, Bill& bill)
{
    // ===== MEMBER 3 : START =====
    // TODO: order.setPaymentDetails(...), order.setOrderStatus("Paid"), bill.setPaymentStatus("Paid").
    // ===== MEMBER 3 : END =====
}
