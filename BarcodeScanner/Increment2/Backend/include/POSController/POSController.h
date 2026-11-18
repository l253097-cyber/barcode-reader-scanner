#ifndef POSCONTROLLER_H
#define POSCONTROLLER_H

#include "Managers/ProductManager.h"
#include "Managers/OrderManager.h"
#include "Managers/BillManager.h"
#include "Managers/PaymentManager.h"
#include "Camera/CameraHandler.h"
#include "FileHandlers/ProductFileHandler.h"
#include "FileHandlers/OrderFileHandler.h"
#include "FileHandlers/BillFileHandler.h"   // ASSUMED path, same folder as the other two
#include "Models/OrderDetail.h"
#include "Models/Bill.h"
#include <string>

/*
 * ============================================================
 *  POSController
 *  Bridge between GUI and backend. GUI calls ONLY this class. (Reuses Increment 1 BarcodeScanner/Decoder.)
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 5 : handleBarcodeScan(), handleProductDescription(), handleOrderRecording(), handleBillGeneration(), handlePayment()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class POSController {
private:
    ProductManager* productManager = nullptr;
    OrderManager* orderManager = nullptr;
    BillManager* billManager = nullptr;
    PaymentManager* paymentManager = nullptr;
    CameraHandler* cameraHandler = nullptr;
    ProductFileHandler* productFileHandler = nullptr;
    OrderFileHandler* orderFileHandler = nullptr;
    BillFileHandler* billFileHandler = nullptr;

public:
    // ---------- PRE-WRITTEN ----------
    POSController(ProductManager* pm, OrderManager* om, BillManager* bm, PaymentManager* pay,
                  CameraHandler* cam, ProductFileHandler* pfh, OrderFileHandler* ofh, BillFileHandler* bfh)
        : productManager(pm), orderManager(om), billManager(bm), paymentManager(pay), cameraHandler(cam),
        productFileHandler(pfh), orderFileHandler(ofh), billFileHandler(bfh) {}
    CameraHandler* getCameraHandler() const { return cameraHandler; }   // for the GUI camera preview

    // ---------- ASSIGNED FUNCTIONS (written in the .cpp) ----------
    bool handleBarcodeScan(std::string& outBarcode, std::string& outMessage);   // Member 5
    bool handleBarcodeScanFromImage(const std::string& imagePath, std::string& outBarcode, std::string& outMessage);   // decode a saved image (testing)
    bool handleBarcodeGeneration(const std::string& digits, std::string& outFilePath, std::string& outMessage);   // create a barcode image
    std::string handleProductDescription(const std::string& barcode) const;   // Member 5
    bool handleOrderRecording(const std::string& customerName, const std::string& customerContact, const std::string& barcode, int quantity);   // Member 5
    bool handleRemoveProduct(const std::string& barcode);
    Bill handleBillGeneration();   // Member 5
    bool handlePayment(double amount, const std::string& mode, const std::string& merchant);   // Member 5

    // ---------- GETTERS FOR THE GUI ----------
    const OrderDetail* getOrderItems() const;
    int getOrderItemCount() const;
};

#endif // POSCONTROLLER_H