#ifndef BILLMANAGER_H
#define BILLMANAGER_H

#include "Models/Bill.h"
#include "Models/Order.h"
#include "Models/OrderDetail.h"
#include "Managers/ProductManager.h"
#include <string>

/*
 * ============================================================
 *  BillManager
 *  All bill calculations (subtotal, discount, tax, payable) and bill generation.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 3 : calculateSubtotal(), calculateTotalDiscount(), calculateTotalTax(), calculatePayableAmount(), generateBill()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class BillManager {
private:
    Bill currentBill;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    BillManager() = default;
    const Bill& getCurrentBill() const { return currentBill; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    double calculateSubtotal(const OrderDetail* items, int count, const ProductManager& pm) const;   // Member 3
    double calculateTotalDiscount(const OrderDetail* items, int count, const ProductManager& pm) const;   // Member 3
    double calculateTotalTax(const OrderDetail* items, int count, const ProductManager& pm) const;   // Member 3
    double calculatePayableAmount(double subtotal, double totalTax, double totalDiscount) const;   // Member 3
    Bill generateBill(const Order& order, const OrderDetail* items, int count, const ProductManager& pm);   // Member 3
};

#endif // BILLMANAGER_H
