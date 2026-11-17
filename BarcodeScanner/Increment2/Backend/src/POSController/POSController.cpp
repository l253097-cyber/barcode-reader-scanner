#include "POSController/POSController.h"
#include "BarcodeScanner.h"   
#include "BarcodeDecoder.h"
#include "Config.h"
#include <QImage>
#include <QColor>
using namespace std;
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
string frameToPattern(const QImage& frame)
{
    if (frame.isNull()) return "";

    const int y = frame.height() / 2;      // scan the middle row
    const int srcWidth = frame.width();

    // Pick a threshold from the darkest and lightest pixel on the row
    int lo = 255, hi = 0;
    for (int x = 0; x < srcWidth; ++x) {
        int g = qGray(frame.pixel(x, y));
        if (g < lo) lo = g;
        if (g > hi) hi = g;
    }
    if (hi - lo < 40) return "";           // not enough contrast
    const int threshold = (lo + hi) / 2;

    // Find the first and last dark pixel (crop the white margins)
    int first = -1, last = -1;
    for (int x = 0; x < srcWidth; ++x) {
        if (qGray(frame.pixel(x, y)) < threshold) {
            if (first == -1) first = x;
            last = x;
        }
    }
    if (first == -1) return "";

    const int cropWidth = last - first + 1;
    const int targetWidth = (cropWidth < MAX_WIDTH) ? cropWidth : MAX_WIDTH;

    // Build a one-row matrix: 1 = bar (dark), 0 = space
    static int matrix[1][MAX_WIDTH];
    for (int i = 0; i < MAX_WIDTH; ++i) matrix[0][i] = 0;
    for (int i = 0; i < targetWidth; ++i) {
        int srcX = first + (i * cropWidth) / targetWidth;
        matrix[0][i] = (qGray(frame.pixel(srcX, y)) < threshold) ? 1 : 0;
    }

    // Increment 1 pipeline
    char rowPixels[MAX_WIDTH + 1];
    if (!BarcodeScanner::scanPixelRow(matrix, targetWidth, 1, 0, rowPixels))
        return "";

    int widths[MAX_WIDTH];
    int runCount = BarcodeScanner::detectBarWidths(rowPixels, widths, MAX_WIDTH);
    if (runCount == 0) return "";

    return BarcodeScanner::widthsToPattern(rowPixels, widths, runCount);
}
bool POSController::handleBarcodeScan(std::string& outBarcode, std::string& outMessage)
{
        // ===== MEMBER 5 : START =====
    outBarcode.clear();
    outMessage.clear();

    if (cameraHandler == nullptr || productManager == nullptr) {
        outMessage = "System is not initialized properly.";
        return false;
    }

    if (!cameraHandler->isCameraAvailable() || !cameraHandler->checkCameraStatus()) {
        outMessage = "Camera is not available.";
        return false;
    }

    if (!cameraHandler->captureFrame()) {
        outMessage = "Could not capture a frame from the camera.";
        return false;
    }

    QImage frame = cameraHandler->convertFrameToImageData();
    if (frame.isNull()) {
        outMessage = "Captured frame is empty. Try again.";
        return false;
    }

    std::string pattern = frameToPattern(frame);
    if (pattern.empty()) {
        outMessage = "No barcode detected. Hold the barcode steady and try again.";
        return false;
    }

    std::string decoded = BarcodeDecoder::decodeScannedPattern(pattern);
    if (decoded.empty() || !BarcodeDecoder::verifyDecodedResult(decoded)) {
        outMessage = "Barcode could not be decoded. Try again.";
        return false;
    }

    if (productManager->findProductByBarcode(decoded) == nullptr) {
        outMessage = "Barcode " + decoded + " is not in the product list.";
        return false;
    }

    outBarcode = decoded;
    outMessage = "Barcode scanned successfully.";
    return true;
    }

std::string POSController::handleProductDescription(const std::string& barcode) const
{
    // ===== MEMBER 5 : START =====
    if (productManager == nullptr || barcode.empty()) {
        return "";
    }
    return productManager->getProductDescription(barcode);
    // ===== MEMBER 5 : END =====
}

bool POSController::handleOrderRecording(const std::string& customerName, const std::string& customerContact, const std::string& barcode, int quantity)
{
    // ===== MEMBER 5 : START =====
    if (productManager == nullptr || orderManager == nullptr || orderFileHandler == nullptr) {
        return false;
    }
    if (barcode.empty() || quantity <= 0) {
        return false;
    }

    // Start a new order only if there is none yet
    if (orderManager->getCurrentOrder().getOrderId().empty()) {
        if (customerName.empty() || !orderManager->createOrder(customerName, customerContact)) {
            return false;
        }
    }

    Product* product = productManager->findProductByBarcode(barcode);
    if (product == nullptr) {
        return false;   // unknown barcode
    }

    if (!productManager->checkAvailableQuantity(product->getProductId(), quantity)) {
        return false;   // not enough stock
    }

    if (!orderManager->addProductToOrder(*product, quantity)) {
        return false;
    }

    if (!orderManager->validateOrder(*productManager)) {
        orderManager->removeProductFromOrder(product->getProductId());   // roll back
        return false;
    }

    return orderFileHandler->saveOrder(orderManager->getCurrentOrder());
    // ===== MEMBER 5 : END =====
}

bool POSController::handleRemoveProduct(const std::string& barcode)
{
    if (productManager == nullptr || orderManager == nullptr)
    {
        return false;
    }

    if (barcode.empty())
    {
        return false;
    }

    Product* product = productManager->findProductByBarcode(barcode);

    if (product == nullptr)
    {
        return false;
    }

    return orderManager->removeProductFromOrder(product->getProductId());
}

Bill POSController::handleBillGeneration()
{
    // ===== MEMBER 5 : START =====
    if (productManager == nullptr || orderManager == nullptr ||
        billManager == nullptr || billFileHandler == nullptr) {
        return Bill();
    }
    if (orderManager->getDetailCount() == 0) {
        return Bill();   // nothing to bill
    }

    Bill bill = billManager->generateBill(orderManager->getCurrentOrder(),
        orderManager->getOrderDetails(),
        orderManager->getDetailCount(),
        *productManager);

    billFileHandler->saveBill(bill);   // ASSUMED: saveBill(const Bill&)
    return bill;
    // ===== MEMBER 5 : END =====
}

bool POSController::handlePayment(double amount, const std::string& mode, const std::string& merchant)
{
    if (productManager == nullptr || orderManager == nullptr || billManager == nullptr ||
        paymentManager == nullptr || productFileHandler == nullptr ||
        orderFileHandler == nullptr || billFileHandler == nullptr) {
        return false;
    }

    const int count = orderManager->getDetailCount();
    if (count == 0) {
        return false;   // nothing to pay for
    }

    // The bill must have been generated first (handleBillGeneration)
    const Bill& currentBill = billManager->getCurrentBill();
    const double payable = currentBill.getPayableAmount();
    if (payable <= 0.0) {
        return false;
    }

    // Validates and processes the payment
    if (!paymentManager->processPayment(amount, payable, mode, merchant)) {
        return false;
    }

    // Record payment on the order, then let PaymentManager update order + bill status.
    // getCurrentBill() is const, so work on a copy of the bill.
    Order& order = orderManager->getCurrentOrder();
    order.setPaymentDetails(amount, mode, merchant);

    Bill paidBill = currentBill;
    paymentManager->updateOrderPaymentStatus(order, paidBill);

    // Deduct stock for every item in the order
    const OrderDetail* details = orderManager->getOrderDetails();
    for (int i = 0; i < count; ++i) {
        productManager->deductStock(details[i].getProductId(), details[i].getQuantity());
    }

    // Save everything (ASSUMED file handler signatures)
    bool ok = true;
    ok = orderFileHandler->saveOrder(order) && ok;
    ok = billFileHandler->saveBill(paidBill) && ok;
    ok = productFileHandler->saveProducts(productManager->getProducts(),
        productManager->getProductCount()) && ok;
    return ok;
}
const OrderDetail* POSController::getOrderItems() const
{
    if (orderManager == nullptr)
        return nullptr;

    return orderManager->getOrderDetails();
}

int POSController::getOrderItemCount() const
{
    if (orderManager == nullptr)
        return 0;

    return orderManager->getDetailCount();
}