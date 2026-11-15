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
    double subtotal = 0.0;
    for (int i = 0; i < count; i++)
    {
        Product* p = pm.findProductByBarcode(items[i].getProductBarcode());   // CHECK 1
        if (p == nullptr)
            continue;                       // unknown product: skip it
        subtotal += p->getUnitPrice() * items[i].getQuantity();
    }
    return subtotal;
    // ===== MEMBER 3 : END =====
}

double BillManager::calculateTotalDiscount(const OrderDetail* items, int count, const ProductManager& pm) const
{
    // ===== MEMBER 3 : START =====
    double totalDiscount = 0.0;
    for (int i = 0; i < count; i++)
    {
        const Product* p = pm.findProductByBarcode(items[i].getProductBarcode());
        if (p == nullptr)
            continue;
        totalDiscount += p->getDiscount() * items[i].getQuantity();   // discount is per unit
    }
    return totalDiscount;
    // ===== MEMBER 3 : END =====
}

double BillManager::calculateTotalTax(const OrderDetail* items, int count, const ProductManager& pm) const
{
    // ===== MEMBER 3 : START =====
    
    // ===== MEMBER 3 : END =====
}

double BillManager::calculatePayableAmount(double subtotal, double totalTax, double totalDiscount) const
{
    // ===== MEMBER 3 : START =====
    // TODO: subtotal - totalDiscount + totalTax.
  
    // ===== MEMBER 3 : END =====
}

Bill BillManager::generateBill(const Order& order, const OrderDetail* items, int count, const ProductManager& pm)
{
    // ===== MEMBER 3 : START =====
    // TODO: Call the 4 calculate functions, build a Bill (new billId, paymentStatus "Unpaid"), store in currentBill and return it.
    return {};
    // ===== MEMBER 3 : END =====
}
