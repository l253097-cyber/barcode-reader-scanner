#ifndef ORDER_H
#define ORDER_H

#include <string>

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

class Order {
private:
    std::string orderId;
    std::string orderDate;
    std::string orderTime;
    std::string customerName;
    std::string customerContact;
    std::string orderStatus;
    double paymentAmount = 0.0;
    std::string paymentMode;
    std::string paymentMerchant;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    Order() = default;
    Order(const std::string& orderId, const std::string& orderDate, const std::string& orderTime, const std::string& customerName, const std::string& customerContact, const std::string& orderStatus, double paymentAmount, const std::string& paymentMode, const std::string& paymentMerchant) : orderId(orderId), orderDate(orderDate), orderTime(orderTime), customerName(customerName), customerContact(customerContact), orderStatus(orderStatus), paymentAmount(paymentAmount), paymentMode(paymentMode), paymentMerchant(paymentMerchant) {}
    const std::string& getOrderId() const { return orderId; }
    const std::string& getOrderDate() const { return orderDate; }
    const std::string& getOrderTime() const { return orderTime; }
    const std::string& getCustomerName() const { return customerName; }
    const std::string& getCustomerContact() const { return customerContact; }
    const std::string& getOrderStatus() const { return orderStatus; }
    double getPaymentAmount() const { return paymentAmount; }
    const std::string& getPaymentMode() const { return paymentMode; }
    const std::string& getPaymentMerchant() const { return paymentMerchant; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    void setOrderStatus(const std::string& status);   // Member 2
    void setPaymentDetails(double amount, const std::string& mode, const std::string& merchant);   // Member 2
};

#endif // ORDER_H
