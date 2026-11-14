#ifndef PRODUCTFILEHANDLER_H
#define PRODUCTFILEHANDLER_H

#include "Common/Config.h"
#include <string>
#include "Models/Product.h"

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

class ProductFileHandler {
private:
    std::string fileName;
    Product* products = nullptr;
    int productCount = 0;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    explicit ProductFileHandler(const std::string& fileName = std::string(POS_DATA_DIR) + "Product.txt") : fileName(fileName) {}
    ~ProductFileHandler() { delete[] products; }
    ProductFileHandler(const ProductFileHandler&) = delete;
    ProductFileHandler& operator=(const ProductFileHandler&) = delete;
    const Product* getProducts() const { return products; }
    int getProductCount() const { return productCount; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool loadProducts();   // Member 5
    bool parseProductRecord(const std::string& line, Product& outProduct) const;   // Member 5
    bool saveProducts(const Product* list, int count) const;   // Member 5
    std::string serializeProductRecord(const Product& product) const;   // Member 5
};

#endif // PRODUCTFILEHANDLER_H
