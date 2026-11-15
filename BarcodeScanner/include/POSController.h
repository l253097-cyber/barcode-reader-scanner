#ifndef POSCONTROLLER_H
#define POSCONTROLLER_H

#include "Managers/ProductManager.h"
#include "Managers/OrderManager.h"
#include "Managers/BillManager.h"
#include "Managers/PaymentManager.h"
#include "Camera/CameraHandler.h"
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

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    POSController(ProductManager* pm, OrderManager* om, BillManager* bm, PaymentManager* pay, CameraHandler* cam)
        : productManager(pm), orderManager(om), billManager(bm), paymentManager(pay), cameraHandler(cam) {}
    CameraHandler* getCameraHandler() const { return cameraHandler; }   // for the GUI camera preview
    // Member 5 may add more small getters here when the GUI needs them (e.g. current order items).

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool handleBarcodeScan(std::string& outBarcode, std::string& outMessage);   // Member 5
    std::string handleProductDescription(const std::string& barcode) const;   // Member 5
    bool handleOrderRecording(const std::string& customerName, const std::string& customerContact, const std::string& barcode, int quantity);   // Member 5
    Bill handleBillGeneration();   // Member 5
    bool handlePayment(double amount, const std::string& mode, const std::string& merchant);   // Member 5
};

#endif // POSCONTROLLER_H
