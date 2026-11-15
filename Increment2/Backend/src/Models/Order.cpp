#include "Models/Order.h"

// ===== MEMBER 2 =====
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
    
    if (amount < 0)
    {
        return;
    }
    paymentAmount = amount;
    paymentMode = mode;
    paymentMerchant = merchant;
}
