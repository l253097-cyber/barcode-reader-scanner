#include "Models/Product.h"

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

bool Product::updateStock(int quantitySold)
{
    // ===== MEMBER 1 : START =====
    //Reduce availableQuantity by quantitySold. Return false (and change nothing) if quantitySold <= 0 or more than available.
    if (quantitySold <= 0 || quantitySold > availableQuantity)
        return false;               // nothing changes on a bad request

    availableQuantity -= quantitySold;
    return true;
    // ===== MEMBER 1 : END =====
}
