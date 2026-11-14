#include "Models/Order.h"

/*
 * ============================================================
 *  Order
 *  Data class: one customer order (Order.txt).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 2 : setOrderStatus(), setPaymentDetails()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

void Order::setOrderStatus(const std::string& status)
{
    if (status == "")
    {
        return;
    }
    orderStatus = status;
}

void Order::setPaymentDetails(double amount, const std::string& mode, const std::string& merchant)
{
    // ===== MEMBER 2 : START =====
    // TODO: Store paymentAmount, paymentMode (cash/card/wallet) and paymentMerchant.
    // ===== MEMBER 2 : END =====
}
