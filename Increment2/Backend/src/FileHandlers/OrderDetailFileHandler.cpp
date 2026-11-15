#include "FileHandlers/OrderDetailFileHandler.h"
#include <fstream>

static bool toInt(const std::string& text, int& result)
{
    if (text == "")
    {
        return false;
    }
    int value = 0;
    for (int i = 0; i < (int)text.length(); i++)
    {
        if (text[i] < '0' || text[i] > '9')
        {
            return false;   
        }
        value = value * 10 + (text[i] - '0');
    }
    result = value;
    return true;
}

bool OrderDetailFileHandler::saveOrderDetails(const OrderDetail* items, int count) const
{
    // ===== MEMBER 5 =====

}

int OrderDetailFileHandler::loadOrderDetails(OrderDetail* outItems, int maxCount) const
{
    // ===== MEMBER 2 : START =====
    // TODO: Read file, parseOrderDetailRecord() each line, return count.
    return 0;
    // ===== MEMBER 2 : END =====
}

//bool OrderDetailFileHandler::parseOrderDetailRecord(const std::string& line, OrderDetail& outItem) const
{

}

std::string OrderDetailFileHandler::serializeOrderDetailRecord(const OrderDetail& item) const
{
    // ===== MEMBER 2 =====
    //record format: orderId|productId|productBarcode|quantity
        
    return item.getOrderId() + "|" + std::to_string(item.getProductId()) +
        "|" + item.getProductBarcode() + "|" + std::to_string(item.getQuantity());
}
