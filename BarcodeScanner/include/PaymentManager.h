#ifndef PAYMENTMANAGER_H
#define PAYMENTMANAGER_H

#include "Models/Order.h"
#include "Models/Bill.h"
#include <string>

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

class PaymentManager {
private:
    double paymentAmount = 0.0;
    std::string paymentMode;
    std::string paymentMerchant;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    PaymentManager() = default;

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool validatePayment(double amount, double payableAmount, const std::string& mode, const std::string& merchant) const;   // Member 3
    bool processPayment(double amount, double payableAmount, const std::string& mode, const std::string& merchant);   // Member 3
    void updateOrderPaymentStatus(Order& order, Bill& bill);   // Member 3
};

#endif // PAYMENTMANAGER_H
