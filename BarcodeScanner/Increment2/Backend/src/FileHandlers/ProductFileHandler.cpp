#include "FileHandlers/ProductFileHandler.h"
#include "Config.h"
#include <fstream>
#include <sstream>
#include <vector>

/*
- ============================================================
-  ProductFileHandler
-  Reads/writes Product.txt. Record format (one per line, '|' separated): productId|barcode|acronym|name|unit|unitPrice|tax|discount|quantity|barcodeFilePath
- ------------------------------------------------------------
-  WHO WRITES WHAT (function ownership):
-    Member 5 : loadProducts(), parseProductRecord(), saveProducts(), serializeProductRecord()
-  Pre-written (getters/constructors): already done, don't touch.
-  Rule: only edit the function bodies marked with YOUR member number.
- ============================================================
 */

bool ProductFileHandler::loadProducts()
{
    // ===== MEMBER 5 : START =====
    productCount = 0;
    const int maxCapacity = static_cast<int>(sizeof(products) / sizeof(products[0]));
    const std::string path = std::string(POS_DATA_DIR) + "Product.txt";
    std::ifstream inFile(path);
    if (!inFile.is_open())
        return false;

    std::string line;
    while (std::getline(inFile, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty())
            continue;

        Product parsed;
        if (parseProductRecord(line, parsed) && productCount < maxCapacity)
        {
            products[productCount++] = parsed;
        }
    }
    return true;
    // ===== MEMBER 5 : END =====
}

bool ProductFileHandler::parseProductRecord(const std::string& line, Product& outProduct) const
{
    // ===== MEMBER 5 : START =====
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, '|'))
    {
        fields.push_back(item);
    }
    if (!line.empty() && line.back() == '|')
        fields.push_back("");

    if (fields.size() < 10)
        return false;

    try {
        int productId               = std::stoi(fields[0]);
        std::string barcode         = fields[1];
        std::string acronym         = fields[2];
        std::string productName     = fields[3];
        std::string measurementUnit = fields[4];
        double unitPrice            = std::stod(fields[5]);
        double tax                  = std::stod(fields[6]);
        double discount             = std::stod(fields[7]);
        int availableQuantity       = std::stoi(fields[8]);
        std::string barcodeFilePath = fields[9];

        if (productId <= 0 || barcode.empty() || productName.empty())
            return false;

        outProduct = Product(productId, barcode, acronym, productName, measurementUnit,
                             unitPrice, tax, discount, availableQuantity, barcodeFilePath);
        return true;
    } catch (...) {
        return false;
    }
    // ===== MEMBER 5 : END =====
}

bool ProductFileHandler::saveProducts(const Product* list, int count) const
{
    // ===== MEMBER 5 : START =====
    if (list == nullptr || count < 0)
        return false;

    const std::string path = std::string(POS_DATA_DIR) + "Product.txt";
    std::ofstream outFile(path, std::ios::trunc);
    if (!outFile.is_open())
        return false;

    for (int i = 0; i < count; ++i)
    {
        outFile << serializeProductRecord(list[i]) << "\n";
    }
    return true;
    // ===== MEMBER 5 : END =====
}

std::string ProductFileHandler::serializeProductRecord(const Product& product) const
{
    // ===== MEMBER 5 : START =====
    std::ostringstream oss;
    oss << product.getProductId() << "|"
        << product.getBarcode() << "|"
        << product.getAcronym() << "|"
        << product.getProductName() << "|"
        << product.getMeasurementUnit() << "|"
        << product.getUnitPrice() << "|"
        << product.getTax() << "|"
        << product.getDiscount() << "|"
        << product.getAvailableQuantity() << "|"
        << product.getBarcodeFilePath();
    return oss.str();
    // ===== MEMBER 5 : END =====
}