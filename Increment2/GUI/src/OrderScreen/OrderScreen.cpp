#include "OrderScreen/OrderScreen.h"

/*
 * ============================================================
 *  OrderScreen
 *  Order screen: customer info, order items table, add/remove/description/generate-bill.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 3 : setupOrderScreen(), displayOrderItems(), handleAddProduct(), handleQuantityInput(), handleGenerateBillButton() [EXTRA]
 *    Member 4 : handleDescriptionButton(), handleRemoveProduct()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

void OrderScreen::setupOrderScreen()
{
    // ===== MEMBER 3 : START =====
    // TODO: Create all widgets and layout, connect every button to its slot.
    // ===== MEMBER 3 : END =====
}

void OrderScreen::displayOrderItems(const OrderDetail* items, int count)
{
    // ===== MEMBER 3 : START =====
    // TODO: Fill orderItemsTable: one row per item (product, quantity).
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleAddProduct()
{
    // ===== MEMBER 3 : START =====
    // TODO: Read name/contact/quantity inputs, call controller->handleOrderRecording(...), refresh the table.
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleQuantityInput(const QString& text)
{
    // ===== MEMBER 3 : START =====
    // TODO: Validate that text is a positive whole number; disable Add button otherwise.
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleDescriptionButton()
{
    // ===== MEMBER 4 : START =====
    // TODO: Get selected row's barcode, call controller->handleProductDescription(), send result to ProductDescriptionScreen and open it.
    // ===== MEMBER 4 : END =====
}

void OrderScreen::handleRemoveProduct()
{
    // ===== MEMBER 4 : START =====
    // TODO: Remove the selected row's product from the order, refresh the table.
    // ===== MEMBER 4 : END =====
}

void OrderScreen::handleGenerateBillButton()
{
    // ===== MEMBER 3 (EXTRA - not in the official final list) : START =====
    // TODO: Call controller->handleBillGeneration() and open the Bill screen.
    // ===== MEMBER 3 (EXTRA - not in the official final list) : END =====
}
