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

double BillManager::calculateSubtotal(const OrderDetail* items, int count, ProductManager& pm) const
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

double BillManager::calculateTotalDiscount(const OrderDetail* items, int count, ProductManager& pm) const
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

double BillManager::calculateTotalTax(const OrderDetail* items, int count, ProductManager& pm) const
{
    // ===== MEMBER 3 : START =====
    double totalTax = 0.0;
    for (int i = 0; i < count; i++)
    {
        const Product* p = pm.findProductByBarcode(items[i].getProductBarcode());
        if (p == nullptr)
            continue;
        double priceAfterDiscount = p->getUnitPrice() - p->getDiscount();
        if (priceAfterDiscount < 0.0)
            priceAfterDiscount = 0.0;
        totalTax += priceAfterDiscount * (p->getTax() / 100.0) * items[i].getQuantity();   // tax is a %
    }
    return totalTax;
    // ===== MEMBER 3 : END =====
}

double BillManager::calculatePayableAmount(double subtotal, double totalTax, double totalDiscount) const
{
    // ===== MEMBER 3 : START =====
    // TODO: subtotal - totalDiscount + totalTax.
    double payable = subtotal - totalDiscount + totalTax;
    if (payable < 0.0)
        payable = 0.0;
    return payable;
    // ===== MEMBER 3 : END =====
}

Bill BillManager::generateBill(const Order& order, const OrderDetail* items, int count,ProductManager& pm)
{
    // ===== MEMBER 3 : START =====
    // TODO: Call the 4 calculate functions, build a Bill (new billId, paymentStatus "Unpaid"), store in currentBill and return it.
    double subtotal = calculateSubtotal(items, count, pm);
    double totalDiscount = calculateTotalDiscount(items, count, pm);
    double totalTax = calculateTotalTax(items, count, pm);
    double payable = calculatePayableAmount(subtotal, totalTax, totalDiscount);
    std::string acronym;
    double unitPrice = 0.0, discountPerUnit = 0.0;
    int quantity = 0;
    if (count > 0)
    {
        const Product* p = pm.findProductByBarcode(items[0].getProductBarcode());
        if (p != nullptr)
        {
            acronym = p->getAcronym();
            unitPrice = p->getUnitPrice();
            discountPerUnit = p->getDiscount();
        }
        quantity = items[0].getQuantity();
    }

    static int billCounter = 1;                                        // CHECK 4
    std::string billId = "BILL" + std::to_string(billCounter++);

    Bill bill(billId, order.getCustomerName(), order.getOrderId(), acronym,
        unitPrice, discountPerUnit, quantity,
        subtotal, totalTax, totalDiscount, payable, "Unpaid");   // CHECK 2
    currentBill = bill;
    return bill;
    // ===== MEMBER 3 : END =====
}
