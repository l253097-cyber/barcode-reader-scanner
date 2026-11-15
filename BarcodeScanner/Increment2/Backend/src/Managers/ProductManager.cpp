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

 // Member 1 helper (file-local): position of a barcode in the list, or -1.
 // The search loop lives here once, so the find/description/check functions share it.
static int indexOfBarcode(const Product* list, int count, const std::string& barcode)
{
    for (int i = 0; i < count; ++i)
    {
        if (list[i].getBarcode() == barcode)
            return i;
    }
    return -1;
}

Product* ProductManager::findProductByBarcode(const std::string& barcode)
{
    // ===== MEMBER 1 : START =====
    //Loop over products[], return pointer to the match, else nullptr.
    int i = indexOfBarcode(products, productCount, barcode);
    return (i >= 0) ? &products[i] : nullptr;
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
