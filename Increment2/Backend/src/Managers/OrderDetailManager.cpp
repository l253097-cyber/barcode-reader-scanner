#include "Managers/OrderDetailManager.h"

/*
 * ============================================================
 *  OrderDetailManager
 *  Manages the list of all order-detail records (load/search/update/remove).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 4 : addOrderDetail(), getOrderDetails(), findOrderDetail(), updateOrderDetailQuantity(), removeOrderDetail()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

bool OrderDetailManager::addOrderDetail(const OrderDetail& detail)
{
    // ===== MEMBER 4 : START =====
	//check if the order detail is valid (non-empty orderId, positive productId, positive quantity, non-empty productBarcode)
	if (detail.getOrderId().empty() || detail.getProductId() <= 0 || detail.getQuantity() < 1 || detail.getProductBarcode().empty())
		return false; //returns false if the order detail is invalid
	//if the order detail is valid, check if it already exists in the list
	OrderDetail* existingitem = findOrderDetail(detail.getOrderId(), detail.getProductId());
	//if this product already exits in our order so we just update its quantity instead of adding a new record
    if (existingitem != nullptr)
    {
		existingitem->setQuantity(existingitem->getQuantity() + detail.getQuantity());
		return true;
    }
    //returns false if the order detail list is full
	if (detailCount >= MAX_DETAILS)
		return false; 
	//if the order detail does not exist, we add it to the list
	details[detailCount] = detail;
    detailCount++;
	return true;
    // ===== MEMBER 4 : END =====
}
//useful for bill or to show on screen 
//maxCount = how many OrderDetail objects outArray can hold
int OrderDetailManager::getOrderDetails(const std::string& orderId, OrderDetail* outArray, int maxCount) const
{
    // ===== MEMBER 4 : START =====
     // Return 0 if the output array is not alloacted yet  or maxCount is non-positive
	if (outArray == nullptr || maxCount <= 0)
		return 0;
    int idx = 0;
	for (int i = 0; i < detailCount && idx < maxCount; i++)
	{
		if (details[i].getOrderId() == orderId)
		{
			outArray[idx] = details[i];
			idx++;
		}
	}
	return idx; // Return the number of order details copied to outArray

    // ===== MEMBER 4 : END =====
}
//to be used by cashier if he updates / removes any product 
//it searches for specific detail in order 
OrderDetail* OrderDetailManager::findOrderDetail(const std::string& orderId, int productId)
{
    // ===== MEMBER 4 : START =====
	
	for (int i = 0;i < detailCount;i++) {
		if (details[i].getOrderId() == orderId && details[i].getProductId() == productId)
		{
			return &details[i];
		}
		}
	

    return nullptr;
    // ===== MEMBER 4 : END =====
}

bool OrderDetailManager::updateOrderDetailQuantity(const std::string& orderId, int productId, int newQuantity)
{
    // ===== MEMBER 4 : START =====
	if (newQuantity < 1)
		return false;
	OrderDetail* tobeupdated = findOrderDetail(orderId, productId);
	if (tobeupdated != nullptr)
	{
		tobeupdated->setQuantity(newQuantity);
		return true;
	}
	return false;
    // ===== MEMBER 4 : END =====
}

bool OrderDetailManager::removeOrderDetail(const std::string& orderId, int productId)
{
    // ===== MEMBER 4 : START =====
	OrderDetail* tobe_removed = findOrderDetail(orderId, productId);
	if (tobe_removed != nullptr)
	{
		// Shift all subsequent elements to the left
		int index = static_cast<int>(tobe_removed - details);
				for (int j = index; j < detailCount - 1; j++)
				{
					details[j] = details[j + 1];
				}
				detailCount--;
				return true;
			
		
	}
    return false;
    // ===== MEMBER 4 : END =====
}
