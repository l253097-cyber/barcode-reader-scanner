#include "ProductFileHandler.h"
using namespace std;
#include<iostream>
#include<fstream>
/*
 * ============================================================
 *  ProductFileHandler
 *  Reads/writes Product.txt. Record format (one per line, '|' separated): productId|barcode|acronym|name|unit|unitPrice|tax|discount|quantity|barcodeFilePath
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 5 : loadProducts(), parseProductRecord(), saveProducts(), serializeProductRecord()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */


bool ProductFileHandler::loadProducts()
{
    // ===== MEMBER 5 : START =====

    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Error: Cannot open Product.txt" << endl;
        return false;
    }

    // Delete previously loaded products
    delete[] products;
    products = nullptr;
    productCount = 0;

    string line;

    Product tempProducts[100];
    int count = 0;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Product p;

        if (!parseProductRecord(line, p))
        {
            cout << "Invalid product record: " << line << endl;

            file.close();
            return false;
        }

        if (count >= 100)
        {
            cout << "Error: Product limit exceeded." << endl;

            file.close();
            return false;
        }

        tempProducts[count] = p;
        count++;
    }

    file.close();

    if (count == 0)
        return true;

    products = new Product[count];

    for (int i = 0; i < count; i++)
    {
        products[i] = tempProducts[i];
    }

    productCount = count;

    return true;

    // ===== MEMBER 5 : END =====
}

 bool ProductFileHandler::parseProductRecord(const string & line, Product & outProduct) const
    {
        // MEMBER 5

        Product p;

        int id, availableAmount;
        string barcode, acronym, name, measurement, barcodeFile;
        double unitPrice, tax, discount;

        int i = 0;

        // 1. Product ID
        string temp = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            if (line[i] < '0' || line[i] > '9')
                return false;

            temp += line[i];
            i++;
        }

        if (line[i] != '|' || temp == "")
            return false;

        id = stoi(temp);
        i++;

        // 2. Barcode
        temp = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            if (line[i] < '0' || line[i] > '9')
                return false;

            temp += line[i];
            i++;
        }

        if (line[i] != '|' || temp == "")
            return false;

        barcode = temp;
        i++;

        // 3. Acronym
        acronym = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            acronym += line[i];
            i++;
        }

        if (line[i] != '|' || acronym == "")
            return false;

        i++;

        // 4. Product name
        name = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            name += line[i];
            i++;
        }

        if (line[i] != '|' || name == "")
            return false;

        i++;

        // 5. Measurement unit
        measurement = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            measurement += line[i];
            i++;
        }

        if (line[i] != '|' || measurement == "")
            return false;

        i++;

        // 6. Unit price
        temp = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            temp += line[i];
            i++;
        }

        if (line[i] != '|' || temp == "")
            return false;

        try
        {
            unitPrice = stod(temp);
        }
        catch (...)
        {
            return false;
        }

        i++;

        // 7. Tax
        temp = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            temp += line[i];
            i++;
        }

        if (line[i] != '|' || temp == "")
            return false;

        try
        {
            tax = stod(temp);
        }
        catch (...)
        {
            return false;
        }

        i++;

        // 8. Discount
        temp = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            temp += line[i];
            i++;
        }

        if (line[i] != '|' || temp == "")
            return false;

        try
        {
            discount = stod(temp);
        }
        catch (...)
        {
            return false;
        }

        i++;

        // 9. Available quantity
        temp = "";

        while (line[i] != '|' && line[i] != '\0')
        {
            if (line[i] < '0' || line[i] > '9')
                return false;

            temp += line[i];
            i++;
        }

        if (line[i] != '|' || temp == "")
            return false;

        availableAmount = stoi(temp);
        i++;

        // 10. Barcode file path
        barcodeFile = "";

        while (line[i] != '\0')
        {
            if (line[i] == '|')
                return false;

            barcodeFile += line[i];
            i++;
        }

        if (barcodeFile == "")
            return false;

        outProduct = Product(
            id, barcode, acronym, name, measurement,
            unitPrice, tax, discount, availableAmount, barcodeFile );

        return true;
}


bool ProductFileHandler::saveProducts(const Product* list, int count) const
{
    // ===== MEMBER 5 : START =====

    if (count < 0)
        return false;

    if (count > 0 && list == nullptr)
        return false;

    ofstream file(fileName);

    if (!file.is_open())
    {
        cout << "Error: Cannot open Product.txt for writing." << endl;
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        file << serializeProductRecord(list[i]);

        if (i < count - 1)
            file << endl;
    }

    if (!file.good())
    {
        file.close();
        return false;
    }

    file.close();

    return true;

    // ===== MEMBER 5 : END =====
}



string ProductFileHandler::serializeProductRecord(const Product& product) const
{
    // ===== MEMBER 5 : START =====

    string line = "";

    line += to_string(product.getProductId()) + "|";
    line += product.getBarcode() + "|";
    line += product.getAcronym() + "|";
    line += product.getProductName() + "|";
    line += product.getMeasurementUnit() + "|";
    line += to_string(product.getUnitPrice()) + "|";
    line += to_string(product.getTax()) + "|";
    line += to_string(product.getDiscount()) + "|";
    line += to_string(product.getAvailableQuantity()) + "|";
    line += product.getBarcodeFilePath();

    return line;

    // ===== MEMBER 5 : END =====
}
