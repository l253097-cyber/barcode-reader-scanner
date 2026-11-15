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
    if (mode.empty())
        return false;
    if (mode != "Cash" && merchant.empty())
        return false;
    if (amount <= 0.0)
        return false;
    if (amount + 0.005 < payableAmount)      // not enough money (0.005 avoids rounding problems)
        return false;
    return true;
    // ===== MEMBER 3 : END =====
}

bool PaymentManager::processPayment(double amount, double payableAmount, const std::string& mode, const std::string& merchant)
{
    // ===== MEMBER 3 : START =====
    // TODO: Call validatePayment(); if OK store values in the data members and return true.
    if (!validatePayment(amount, payableAmount, mode, merchant))
        return false;
    paymentAmount = amount;
    paymentMode = mode;
    paymentMerchant = merchant;
    return true;
    // ===== MEMBER 3 : END =====
}

void PaymentManager::updateOrderPaymentStatus(Order& order, Bill& bill)
{
    // ===== MEMBER 3 : START =====
    // TODO: order.setPaymentDetails(...), order.setOrderStatus("Paid"), bill.setPaymentStatus("Paid").
    if (paymentAmount <= 0.0)                // nothing was paid yet
        return;
    order.setPaymentDetails(paymentAmount, paymentMode, paymentMerchant);
    order.setOrderStatus("Paid");            // CHECK 5
    bill.setPaymentStatus("Paid");
    // ===== MEMBER 3 : END =====
}
