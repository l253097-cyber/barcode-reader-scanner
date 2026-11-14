#include "Managers/BillManager.h"

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

double BillManager::calculateSubtotal(const OrderDetail* items, int count, const ProductManager& pm) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Sum of unitPrice * quantity.
    return 0.0;
    // ===== MEMBER 3 : END =====
}

double BillManager::calculateTotalDiscount(const OrderDetail* items, int count, const ProductManager& pm) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Sum of discount (per unit) * quantity.
    return 0.0;
    // ===== MEMBER 3 : END =====
}

double BillManager::calculateTotalTax(const OrderDetail* items, int count, const ProductManager& pm) const
{
    // ===== MEMBER 3 : START =====
    // TODO: Tax of each item (tax % of price after discount) * quantity, summed.
    return 0.0;
    // ===== MEMBER 3 : END =====
}

double BillManager::calculatePayableAmount(double subtotal, double totalTax, double totalDiscount) const
{
    // ===== MEMBER 3 : START =====
    // TODO: subtotal - totalDiscount + totalTax.
    return 0.0;
    // ===== MEMBER 3 : END =====
}

Bill BillManager::generateBill(const Order& order, const OrderDetail* items, int count, const ProductManager& pm)
{
    // ===== MEMBER 3 : START =====
    // TODO: Call the 4 calculate functions, build a Bill (new billId, paymentStatus "Unpaid"), store in currentBill and return it.
    return {};
    // ===== MEMBER 3 : END =====
}
