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
    return 0;
}

int OrderDetailFileHandler::loadOrderDetails(OrderDetail* outItems, int maxCount) const
{
    // ===== MEMBER 2 =====
    std::ifstream file(fileName.c_str());
    if (file.is_open() == false)
    {
        return 0;   
    }

    int count = 0;
    std::string line;
    while (count < maxCount && std::getline(file, line))
    {
        if (line.length() > 0 && line[line.length() - 1] == '\r')
        {
            line = line.substr(0, line.length() - 1);
        }

        if (line == "")
        {
            continue;
        }

        OrderDetail item;
        if (parseOrderDetailRecord(line, item))
        {
            outItems[count] = item;
            count++;
        }
    }

    file.close();
    return count;
}

bool OrderDetailFileHandler::parseOrderDetailRecord(const std::string& line, OrderDetail& outItem) const
{

    // ===== MEMBER 2 =====
    std::string parts[4];
    int partCount = 0;
    std::string current = "";

    for (int i = 0; i < (int)line.length(); i++)
    {
        char c = line[i];
        if (c == '|')
        {
            if (partCount >= 3)
            {
                return false;
            }
            parts[partCount] = current;
            partCount++;
            current = "";
        }
        else
        {
            current = current + c;
        }
    }

    if (partCount != 3)
    {
        return false;
    }
    parts[3] = current;
    int productId = 0;
    int quantity = 0;
    if (toInt(parts[1], productId) == false)
    {
        return false;
    }
    if (toInt(parts[3], quantity) == false)
    {
        return false;
    }

    if (parts[0] == "" || quantity <= 0)
    {
        return false;
    }

    outItem = OrderDetail(parts[0], productId, parts[2], quantity);
    return true;
}

std::string OrderDetailFileHandler::serializeOrderDetailRecord(const OrderDetail& item) const
{
    // ===== MEMBER 2 =====
    //record format: orderId|productId|productBarcode|quantity
        
    return item.getOrderId() + "|" + std::to_string(item.getProductId()) +
        "|" + item.getProductBarcode() + "|" + std::to_string(item.getQuantity());
}
