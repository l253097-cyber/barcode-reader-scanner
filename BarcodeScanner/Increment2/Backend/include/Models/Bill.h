#ifndef BILL_H
#define BILL_H

#include <string>

/*
 * ============================================================
 *  Bill
 *  Data class: one generated bill (Bill.txt).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 3 : setPaymentStatus()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class Bill {
private:
    std::string billId;
    std::string customerName;
    std::string orderId;
    std::string productAcronym;
    double unitPrice = 0.0;
    double discountPerUnit = 0.0;
    int quantity = 0;
    double subtotal = 0.0;
    double totalTax = 0.0;
    double totalDiscount = 0.0;
    double payableAmount = 0.0;
    std::string paymentStatus;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    Bill() = default;
    Bill(const std::string& billId, const std::string& customerName, const std::string& orderId, const std::string& productAcronym, double unitPrice, double discountPerUnit, int quantity, double subtotal, double totalTax, double totalDiscount, double payableAmount, const std::string& paymentStatus) : billId(billId), customerName(customerName), orderId(orderId), productAcronym(productAcronym), unitPrice(unitPrice), discountPerUnit(discountPerUnit), quantity(quantity), subtotal(subtotal), totalTax(totalTax), totalDiscount(totalDiscount), payableAmount(payableAmount), paymentStatus(paymentStatus) {}
    const std::string& getBillId() const { return billId; }
    const std::string& getCustomerName() const { return customerName; }
    const std::string& getOrderId() const { return orderId; }
    const std::string& getProductAcronym() const { return productAcronym; }
    double getUnitPrice() const { return unitPrice; }
    double getDiscountPerUnit() const { return discountPerUnit; }
    int getQuantity() const { return quantity; }
    double getSubtotal() const { return subtotal; }
    double getTotalTax() const { return totalTax; }
    double getTotalDiscount() const { return totalDiscount; }
    double getPayableAmount() const { return payableAmount; }
    const std::string& getPaymentStatus() const { return paymentStatus; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    void setPaymentStatus(const std::string& status);   // Member 3
};

#endif // BILL_H
