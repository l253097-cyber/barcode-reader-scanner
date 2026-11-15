#include "POSController/POSController.h"

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

bool POSController::handleBarcodeScan(std::string& outBarcode, std::string& outMessage)
{
    // ===== MEMBER 5 : START =====
    // TODO: captureFrame -> convertFrameToImageData -> Increment 1 decoder -> barcode text -> productManager lookup. Fill outBarcode/outMessage.
    return false;
    // ===== MEMBER 5 : END =====
}

std::string POSController::handleProductDescription(const std::string& barcode) const
{
    // ===== MEMBER 5 : START =====
    // TODO: Return productManager->getProductDescription(barcode).
    return "";
    // ===== MEMBER 5 : END =====
}

bool POSController::handleOrderRecording(const std::string& customerName, const std::string& customerContact, const std::string& barcode, int quantity)
{
    // ===== MEMBER 5 : START =====
    // TODO: createOrder if needed, find product, checkAvailableQuantity, addProductToOrder, validate, save with the file handlers.
    return false;
    // ===== MEMBER 5 : END =====
}

Bill POSController::handleBillGeneration()
{
    // ===== MEMBER 5 : START =====
    // TODO: billManager->generateBill(...) from the current order, save with BillFileHandler.
    return {};
    // ===== MEMBER 5 : END =====
}

bool POSController::handlePayment(double amount, const std::string& mode, const std::string& merchant)
{
    // ===== MEMBER 5 : START =====
    // TODO: paymentManager->processPayment, update order/bill status, deductStock for every item, save all files.
    return false;
    // ===== MEMBER 5 : END =====
}
