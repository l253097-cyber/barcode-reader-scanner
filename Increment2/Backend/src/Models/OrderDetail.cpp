#include "Models/OrderDetail.h"

/*
 * ============================================================
 *  OrderDetail
 *  Data class: one product line of an order (OrderDetail.txt).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 4 : setQuantity()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

void OrderDetail::setQuantity(int newQuantity)
{
	// ===== MEMBER 4 : START =====
	// val in order can't be less than 1 but in available stock it can be 0
   //agr new  quantity 1 se chota hai tu purani quantity ko change nahi karna chahiye
	if (newQuantity < 1)
		return;
	quantity = newQuantity;
	// ===== MEMBER 4 : END =====
}
