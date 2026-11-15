// Unit test for OrderDetailManager (plain asserts, no framework needed).
#include <iostream>
#include <cassert>
#include <string>
#include "Managers/OrderDetailManager.h"

// Quantity of one line, or -1 if the line does not exist
// (so a missing line fails an assert instead of crashing on a null pointer).
static int quantityOf(OrderDetailManager& m, const std::string& orderId, int productId)
{
    OrderDetail* line = m.findOrderDetail(orderId, productId);
    return (line == nullptr) ? -1 : line->getQuantity();
}

// ---- addOrderDetail() ----
static void testAdd()
{
    OrderDetailManager m;
    assert(m.getDetailCount() == 0);                                      // starts empty

    assert(m.addOrderDetail(OrderDetail("11111111", 101, "123456", 2)));  // valid line
    assert(m.getDetailCount() == 1);

    // invalid lines are rejected and do not change the count
    assert(!m.addOrderDetail(OrderDetail("", 101, "123456", 1)));          // empty order id
    assert(!m.addOrderDetail(OrderDetail("11111111", 0, "123456", 1)));    // product id 0
    assert(!m.addOrderDetail(OrderDetail("11111111", -5, "123456", 1)));   // negative product id
    assert(!m.addOrderDetail(OrderDetail("11111111", 102, "", 1)));        // empty barcode
    assert(!m.addOrderDetail(OrderDetail("11111111", 102, "123456", 0)));  // quantity 0
    assert(!m.addOrderDetail(OrderDetail("11111111", 102, "123456", -1))); // negative quantity
    assert(m.getDetailCount() == 1);

    // same product in the same order: quantity grows, no new line
    assert(m.addOrderDetail(OrderDetail("11111111", 101, "123456", 3)));
    assert(m.getDetailCount() == 1);
    assert(quantityOf(m, "11111111", 101) == 5);                           // 2 + 3

    // same product in ANOTHER order is a separate line
    assert(m.addOrderDetail(OrderDetail("22222222", 101, "123456", 4)));
    assert(m.getDetailCount() == 2);
}

// ---- findOrderDetail() ----
static void testFind()
{
    OrderDetailManager m;
    m.addOrderDetail(OrderDetail("11111111", 101, "123456", 2));
    m.addOrderDetail(OrderDetail("11111111", 102, "654321", 1));
    m.addOrderDetail(OrderDetail("22222222", 103, "111111", 7));

    OrderDetail* first = m.findOrderDetail("11111111", 101);
    assert(first != nullptr && first->getQuantity() == 2);

    // lines that are NOT in the first slot must be found as well
    OrderDetail* second = m.findOrderDetail("11111111", 102);
    assert(second != nullptr && second->getProductBarcode() == "654321");
    OrderDetail* third = m.findOrderDetail("22222222", 103);
    assert(third != nullptr && third->getQuantity() == 7);

    assert(m.findOrderDetail("11111111", 999) == nullptr);   // unknown product
    assert(m.findOrderDetail("99999999", 101) == nullptr);   // unknown order
    assert(m.findOrderDetail("22222222", 101) == nullptr);   // right product, wrong order
}

// ---- getOrderDetails() ----
static void testGet()
{
    OrderDetailManager m;
    m.addOrderDetail(OrderDetail("11111111", 101, "123456", 2));
    m.addOrderDetail(OrderDetail("22222222", 101, "123456", 4));
    m.addOrderDetail(OrderDetail("11111111", 102, "654321", 1));
    m.addOrderDetail(OrderDetail("11111111", 103, "111111", 5));

    OrderDetail out[10];

    assert(m.getOrderDetails("11111111", out, 10) == 3);     // order 1 has 3 lines
    assert(out[0].getProductId() == 101);                    // in the order they were added
    assert(out[1].getProductId() == 102);
    assert(out[2].getProductId() == 103);
    assert(m.getOrderDetails("22222222", out, 10) == 1);     // order 2 has 1 line
    assert(m.getOrderDetails("99999999", out, 10) == 0);     // unknown order

    assert(m.getOrderDetails("11111111", out, 2) == 2);      // maxCount limits the copy
    assert(m.getOrderDetails("11111111", out, 0) == 0);      // maxCount 0
    assert(m.getOrderDetails("11111111", out, -1) == 0);     // negative maxCount
    assert(m.getOrderDetails("11111111", nullptr, 5) == 0);  // no output array

    out[0].setQuantity(99);                                  // changing the copy ...
    assert(quantityOf(m, "11111111", 101) == 2);             // ... must not change the manager
}

// ---- updateOrderDetailQuantity() ----
static void testUpdate()
{
    OrderDetailManager m;
    m.addOrderDetail(OrderDetail("11111111", 101, "123456", 2));
    m.addOrderDetail(OrderDetail("11111111", 102, "654321", 1));

    assert(m.updateOrderDetailQuantity("11111111", 102, 7));  // existing line
    assert(quantityOf(m, "11111111", 102) == 7);
    assert(quantityOf(m, "11111111", 101) == 2);              // other line untouched

    assert(!m.updateOrderDetailQuantity("11111111", 102, 0));   // 0 rejected
    assert(!m.updateOrderDetailQuantity("11111111", 102, -2));  // negative rejected
    assert(quantityOf(m, "11111111", 102) == 7);                // unchanged after rejection

    assert(!m.updateOrderDetailQuantity("11111111", 999, 3));   // unknown product
    assert(!m.updateOrderDetailQuantity("99999999", 101, 3));   // unknown order
}

// ---- removeOrderDetail() ----
static void testRemove()
{
    OrderDetailManager m;
    m.addOrderDetail(OrderDetail("11111111", 101, "123456", 2));   // slot 0
    m.addOrderDetail(OrderDetail("11111111", 102, "654321", 1));   // slot 1
    m.addOrderDetail(OrderDetail("22222222", 103, "111111", 7));   // slot 2
    m.addOrderDetail(OrderDetail("11111111", 104, "222222", 3));   // slot 3

    assert(m.removeOrderDetail("11111111", 102));                  // a middle line
    assert(m.getDetailCount() == 3);
    assert(m.findOrderDetail("11111111", 102) == nullptr);         // it is gone
    assert(m.findOrderDetail("11111111", 101) != nullptr);         // the others stay
    assert(m.findOrderDetail("22222222", 103) != nullptr);
    assert(m.findOrderDetail("11111111", 104) != nullptr);

    assert(!m.removeOrderDetail("11111111", 102));                 // already removed
    assert(!m.removeOrderDetail("11111111", 999));                 // unknown product
    assert(!m.removeOrderDetail("99999999", 101));                 // unknown order
    assert(m.getDetailCount() == 3);

    assert(m.removeOrderDetail("11111111", 101));                  // first line
    assert(m.removeOrderDetail("11111111", 104));                  // last line
    assert(m.getDetailCount() == 1);
    assert(m.removeOrderDetail("22222222", 103));                  // the only line
    assert(m.getDetailCount() == 0);

    assert(m.addOrderDetail(OrderDetail("33333333", 105, "333333", 1)));   // adding works again
}

// ---- capacity (MAX_DETAILS) ----
static void testCapacity()
{
    OrderDetailManager m;
    bool allAdded = true;
    for (int id = 1; id <= OrderDetailManager::MAX_DETAILS; id++)
        allAdded = allAdded && m.addOrderDetail(OrderDetail("11111111", id, "123456", 1));

    assert(allAdded);
    assert(m.getDetailCount() == OrderDetailManager::MAX_DETAILS);
    assert(!m.addOrderDetail(OrderDetail("11111111", 9999, "123456", 1)));  // full: new product rejected
    assert(m.addOrderDetail(OrderDetail("11111111", 7, "123456", 2)));      // full: existing product still merges
}

int main()
{
    OrderDetailManager obj;   // object must be constructible
    (void)obj;

    // MEMBER 4: tests for addOrderDetail(), getOrderDetails(), findOrderDetail(),
    //           updateOrderDetailQuantity(), removeOrderDetail()
    testAdd();
    testFind();
    testGet();
    testUpdate();
    testRemove();
    testCapacity();

    std::cout << "[TestOrderDetailManager] all tests passed\n";
    return 0;
}