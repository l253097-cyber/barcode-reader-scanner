#include "Managers/ProductManager.h"

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

Product* ProductManager::findProductByBarcode(const std::string& barcode)
{
    // ===== MEMBER 1 : START =====
    // TODO: Loop over products[], return pointer to the match, else nullptr.
    return nullptr;
    // ===== MEMBER 1 : END =====
}

Product* ProductManager::findProductById(int productId)
{
    // ===== MEMBER 1 : START =====
    // TODO: Same as above but compare productId.
    return nullptr;
    // ===== MEMBER 1 : END =====
}

std::string ProductManager::getProductDescription(const std::string& barcode) const
{
    // ===== MEMBER 1 : START =====
    // TODO: Return text: name, unit, price, tax, discount, stock. Return "Product not found" if barcode is unknown.
    return "";
    // ===== MEMBER 1 : END =====
}

bool ProductManager::checkAvailableQuantity(int productId, int quantity) const
{
    // ===== MEMBER 1 : START =====
    // TODO: True only if product exists and availableQuantity >= quantity.
    return false;
    // ===== MEMBER 1 : END =====
}

bool ProductManager::deductStock(int productId, int quantity)
{
    // ===== MEMBER 1 : START =====
    // TODO: Find product and call product->updateStock(quantity). Return its result.
    return false;
    // ===== MEMBER 1 : END =====
}
