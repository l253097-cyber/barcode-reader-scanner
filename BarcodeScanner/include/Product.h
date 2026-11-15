#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

/*
 * ============================================================
 *  Product
 *  Data class: one product record (Product.txt).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 1 : updateStock()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class Product {
private:
    int productId = 0;
    std::string barcode;
    std::string acronym;
    std::string productName;
    std::string measurementUnit;
    double unitPrice = 0.0;
    double tax = 0.0;
    double discount = 0.0;
    int availableQuantity = 0;
    std::string barcodeFilePath;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    Product() = default;
    Product(int productId, const std::string& barcode, const std::string& acronym, const std::string& productName, const std::string& measurementUnit, double unitPrice, double tax, double discount, int availableQuantity, const std::string& barcodeFilePath) : productId(productId), barcode(barcode), acronym(acronym), productName(productName), measurementUnit(measurementUnit), unitPrice(unitPrice), tax(tax), discount(discount), availableQuantity(availableQuantity), barcodeFilePath(barcodeFilePath) {}
    int getProductId() const { return productId; }
    const std::string& getBarcode() const { return barcode; }
    const std::string& getAcronym() const { return acronym; }
    const std::string& getProductName() const { return productName; }
    const std::string& getMeasurementUnit() const { return measurementUnit; }
    double getUnitPrice() const { return unitPrice; }
    double getTax() const { return tax; }
    double getDiscount() const { return discount; }
    int getAvailableQuantity() const { return availableQuantity; }
    const std::string& getBarcodeFilePath() const { return barcodeFilePath; }
    void setAvailableQuantity(int q) { availableQuantity = q; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool updateStock(int quantitySold);   // Member 1
};

#endif // PRODUCT_H
