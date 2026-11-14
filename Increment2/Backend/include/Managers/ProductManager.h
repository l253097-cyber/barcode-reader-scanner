#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "Models/Product.h"
#include <string>

/*
 * ============================================================
 *  ProductManager
 *  Product lookup, description and stock checks (holds products in memory).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 1 : findProductByBarcode(), findProductById(), getProductDescription(), checkAvailableQuantity(), deductStock()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class ProductManager {
private:
    Product* products = nullptr;
    int productCount = 0;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    ProductManager() = default;
    ~ProductManager() { delete[] products; }
    ProductManager(const ProductManager&) = delete;
    ProductManager& operator=(const ProductManager&) = delete;
    // Copies the product list (e.g. from ProductFileHandler) into this manager.
    void setProducts(const Product* src, int count) {
        delete[] products; products = nullptr; productCount = 0;
        if (src && count > 0) { products = new Product[count];
            for (int i = 0; i < count; ++i) products[i] = src[i];
            productCount = count; }
    }
    const Product* getProducts() const { return products; }
    int getProductCount() const { return productCount; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    Product* findProductByBarcode(const std::string& barcode);   // Member 1
    Product* findProductById(int productId);   // Member 1
    std::string getProductDescription(const std::string& barcode) const;   // Member 1
    bool checkAvailableQuantity(int productId, int quantity) const;   // Member 1
    bool deductStock(int productId, int quantity);   // Member 1
};

#endif // PRODUCTMANAGER_H
