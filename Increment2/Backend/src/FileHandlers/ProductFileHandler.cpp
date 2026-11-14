#include "FileHandlers/ProductFileHandler.h"

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
    // TODO: Open file, read line by line, call parseProductRecord(), fill products[] and productCount.
    return false;
    // ===== MEMBER 5 : END =====
}

bool ProductFileHandler::parseProductRecord(const std::string& line, Product& outProduct) const
{
    // ===== MEMBER 5 : START =====
    // TODO: Split line by '|' and fill outProduct. Return false if fields are missing/invalid.
    return false;
    // ===== MEMBER 5 : END =====
}

bool ProductFileHandler::saveProducts(const Product* list, int count) const
{
    // ===== MEMBER 5 : START =====
    // TODO: Write every product with serializeProductRecord(), one per line.
    return false;
    // ===== MEMBER 5 : END =====
}

std::string ProductFileHandler::serializeProductRecord(const Product& product) const
{
    // ===== MEMBER 5 : START =====
    // TODO: Join the 10 fields with '|'.
    return "";
    // ===== MEMBER 5 : END =====
}
