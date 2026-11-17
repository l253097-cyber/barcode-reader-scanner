#include "OrderFileHandler.h"
#include <iostream>
#include <fstream>
#include <string>
/*
 * ============================================================
 *  OrderFileHandler
 *  Reads/writes Order.txt. Record format (one per line, '|' separated): orderId|date|time|customerName|customerContact|status|paymentAmount|paymentMode|paymentMerchant
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 4 : parseOrderRecord(), serializeOrderRecord()
 *    Member 5 : saveOrder(), loadOrders()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */


bool OrderFileHandler::saveOrder(const Order& order) const
{
    // ===== MEMBER 5 : START =====

    ofstream file(fileName, ios::app);

    if (!file.is_open())
    {
        cout << "Error: Cannot open Order.txt for writing." << endl;
        return false;
    }

    file << serializeOrderRecord(order) << endl;

    if (!file.good())
    {
        file.close();
        return false;
    }

    file.close();

    return true;

    // ===== MEMBER 5 : END =====
}



int OrderFileHandler::loadOrders(Order* outOrders, int maxCount) const
{
    // ===== MEMBER 5 : START =====

    if (maxCount < 0 || (maxCount > 0 && outOrders == nullptr))
        return 0;

    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Error: Cannot open Order.txt" << endl;
        return 0;
    }

    string line;
    int count = 0;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Order order;

        if (!parseOrderRecord(line, order))
        {
            cout << "Invalid order record: " << line << endl;

            file.close();
            return -1;
        }

        if (count >= maxCount)
        {
            break;
        }

        outOrders[count] = order;
        count++;
    }

    file.close();

    return count;

    // ===== MEMBER 5 : END =====
}

bool OrderFileHandler::parseOrderRecord(const std::string& line, Order& outOrder) const
{
    // ===== MEMBER 4 : START =====
    // TODO: Split by '|' and build outOrder. (Assigned to Member 4 - not in Part 3 list, see README.)
    return false;
    // ===== MEMBER 4 : END =====
}

std::string OrderFileHandler::serializeOrderRecord(const Order& order) const
{
    // ===== MEMBER 4 : START =====
    // TODO: Join the 9 fields with '|'. (Member 4)
    return "";
    // ===== MEMBER 4 : END =====
}
