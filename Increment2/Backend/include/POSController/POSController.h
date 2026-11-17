#ifndef POSCONTROLLER_H
#define POSCONTROLLER_H

#include "Managers/ProductManager.h"
#include "Managers/OrderManager.h"
#include "Managers/BillManager.h"
#include "Managers/PaymentManager.h"
#include "Camera/CameraHandler.h"
#include <string>

// POSController: GUI aur backend ke beech ka pul.
// GUI sirf isi class se baat karti hai.
class POSController {
private:
    ProductManager* productManager = nullptr;
    OrderManager* orderManager = nullptr;
    BillManager* billManager = nullptr;
    PaymentManager* paymentManager = nullptr;
    CameraHandler* cameraHandler = nullptr;

public:
    POSController(ProductManager* pm, OrderManager* om, BillManager* bm,
        PaymentManager* pay, CameraHandler* cam)
        : productManager(pm), orderManager(om), billManager(bm),
        paymentManager(pay), cameraHandler(cam) {
    }

    // GUI camera preview ke liye
    CameraHandler* getCameraHandler() const { return cameraHandler; }

    // GUI order table ke liye (order ke items)
    const OrderDetail* getOrderItems() const { return orderManager->getOrderDetails(); }
    int getOrderItemCount() const { return orderManager->getDetailCount(); }

    // ----- Member 5 functions -----
    bool handleBarcodeScan(std::string& outBarcode, std::string& outMessage);
    std::string handleProductDescription(const std::string& barcode) const;
    bool handleOrderRecording(const std::string& customerName, const std::string& customerContact,
        const std::string& barcode, int quantity);
    Bill handleBillGeneration();
    bool handlePayment(double amount, const std::string& mode, const std::string& merchant);
    bool handleProductDetails(const std::string& barcode, Product& outProduct) const;
    bool handleRemoveProduct(const std::string& barcode);
};

#endif