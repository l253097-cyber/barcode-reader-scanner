#define _CRT_SECURE_NO_WARNINGS
#include "Managers/OrderManager.h"
#include <ctime>

bool OrderManager::createOrder(const std::string& customerName, const std::string& customerContact)
{
    // ===== MEMBER 2  =====
    if (customerName == "")
    {
        return false;
    }
    detailCount = 0;
    time_t now = time(0);
    tm* t = localtime(&now);
    char dateText[20];
    char timeText[20];
    strftime(dateText, 20, "%Y-%m-%d", t);
    strftime(timeText, 20, "%H:%M:%S", t);

    // Order ID: "ORD" ke saath seconds ka number (har baar alag)
    std::string newId = "ORD" + std::to_string((long long)now);
    // create new order, status pending
    currentOrder = Order(newId, dateText, timeText, customerName, customerContact, "Pending", 0.0, "", "");
    return true;
    
}

bool OrderManager::addProductToOrder(const Product& product, int quantity)
{
    // ===== MEMBER 2 =====
    if (quantity <= 0)
    {
        return false;
    }

    for (int i = 0; i < detailCount; i++)
    {
        if (orderDetails[i].getProductId() == product.getProductId())
        {
            orderDetails[i].setQuantity(orderDetails[i].getQuantity() + quantity);
            return true;
        }
    }
    if (detailCount >= MAX_ITEMS)
    {
        return false;
    }

    orderDetails[detailCount] = OrderDetail(currentOrder.getOrderId(), product.getProductId(), product.getBarcode(), quantity);
    detailCount++;
    return true;
    
}

bool OrderManager::removeProductFromOrder(int productId)
{
    // ===== MEMBER 2 =====
    for (int i = 0; i < detailCount; i++)
    {
        if (orderDetails[i].getProductId() == productId)
        {
            for (int j = i; j < detailCount - 1; j++)
            {
                orderDetails[j] = orderDetails[j + 1];
            }
            detailCount--;
            return true;
        }
    }
    return false;   
}

bool OrderManager::updateProductQuantity(int productId, int newQuantity)
{
    // ===== MEMBER 2 =====
    if (newQuantity <= 0)
    {
        return false;
    }
    for (int i = 0; i < detailCount; i++)
    {
        if (orderDetails[i].getProductId() == productId)
        {
            orderDetails[i].setQuantity(newQuantity);
            return true;
        }
    }
    return false;
}

double OrderManager::calculateOrderSubtotal(const ProductManager& productManager) const
{
    // ===== MEMBER 2 =====
    double total = 0.0;
    for (int i = 0; i < detailCount; i++)
    {
        for (int j = 0; j < productManager.getProductCount(); j++)
        {
            if (productManager.getProducts()[j].getProductId() == orderDetails[i].getProductId())
            {
                total = total + productManager.getProducts()[j].getUnitPrice() * orderDetails[i].getQuantity();
            }
        }
    }
    return total;
}

bool OrderManager::validateOrder(const ProductManager& productManager) const
{
    // ===== MEMBER 2 =====
    if (currentOrder.getCustomerName() == "")
    {
        return false;
    }
    if (detailCount == 0)
    {
        return false;
    }
    for (int i = 0; i < detailCount; i++)
    {
        bool found = false;
        for (int j = 0; j < productManager.getProductCount(); j++)
        {
            if (productManager.getProducts()[j].getProductId() == orderDetails[i].getProductId())
            {
                found = true;
                if (orderDetails[i].getQuantity() > productManager.getProducts()[j].getAvailableQuantity())
                {
                    return false;   
                }
            }
        }
        if (found == false)
        {
            return false;  
        }
    }
    return true;
}
