#include "POSController/POSController.h"
#include "BarcodeScanner.h"
#include "BarcodeDecoder.h"
#include "BarcodeEncoder.h"
#include "Config.h"
#include <QImage>
#include <QColor>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QTransform>
using namespace std;

namespace {

int grayAt(const QImage& img, int x, int y)
{
    int sum = 0, n = 0;
    for (int dy = -2; dy <= 2; ++dy) {
        int yy = y + dy;
        if (yy < 0 || yy >= img.height()) continue;
        sum += qGray(img.pixel(x, yy));
        ++n;
    }
    return (n > 0) ? sum / n : 255;
}

string decodeRowWithThreshold(const QImage& img, int y, bool inverted, int marginPercent, int threshPercent)
{
    const int srcWidth = img.width();

    int lo = 255, hi = 0;
    for (int x = 0; x < srcWidth; ++x) {
        int g = grayAt(img, x, y);
        if (g < lo) lo = g;
        if (g > hi) hi = g;
    }
    if (hi - lo < 30) return "";
    const int threshold = lo + ((hi - lo) * threshPercent) / 100;

    int first = -1, last = -1;
    for (int x = 0; x < srcWidth; ++x) {
        bool dark = grayAt(img, x, y) < threshold;
        bool isBar = inverted ? !dark : dark;
        if (isBar) {
            if (first == -1) first = x;
            last = x;
        }
    }
    if (first == -1 || last - first < 20) return "";

    const int cropWidth = last - first + 1;
    const int margin = (cropWidth * marginPercent) / 100;
    const int total = margin + cropWidth + margin;
    const int targetWidth = (total < MAX_WIDTH) ? total : MAX_WIDTH;

    int matrix[1][MAX_WIDTH];
    for (int i = 0; i < MAX_WIDTH; ++i) matrix[0][i] = 0;
    for (int i = 0; i < targetWidth; ++i) {
        int pos = (i * total) / targetWidth;
        if (pos < margin || pos >= margin + cropWidth) continue;
        int srcX = first + (pos - margin);
        bool dark = grayAt(img, srcX, y) < threshold;
        matrix[0][i] = (inverted ? !dark : dark) ? 1 : 0;
    }

    char rowPixels[MAX_WIDTH + 1];
    if (!BarcodeScanner::scanPixelRow(matrix, targetWidth, 1, 0, rowPixels))
        return "";

    int widths[MAX_WIDTH];
    int runCount = BarcodeScanner::detectBarWidths(rowPixels, widths, MAX_WIDTH);
    if (runCount == 0) return "";

    string pattern = BarcodeScanner::widthsToPattern(rowPixels, widths, runCount);
    if (pattern.empty()) return "";

    string decoded = BarcodeDecoder::decodeScannedPattern(pattern);
    if (decoded.size() != 6) return "";
    if (!BarcodeDecoder::verifyDecodedResult(decoded)) return "";
    return decoded;
}

string scanOrientation(const QImage& img)
{
    const int rowPercents[] = { 50, 45, 55, 40, 60, 35, 65, 30, 70, 25, 75 };
    const int marginChoices[] = { 0, 8 };
    const int threshChoices[] = { 50, 42, 58 };

    for (int r = 0; r < 11; ++r) {
        int y = (img.height() * rowPercents[r]) / 100;
        for (int t = 0; t < 3; ++t) {
            for (int inv = 0; inv < 2; ++inv) {
                for (int m = 0; m < 2; ++m) {
                    string result = decodeRowWithThreshold(img, y, inv == 1, marginChoices[m], threshChoices[t]);
                    if (!result.empty()) return result;
                }
            }
        }
    }
    return "";
}

string decodeFrame(const QImage& frame)
{
    if (frame.isNull() || frame.width() < 40 || frame.height() < 5) return "";

    // 1. Try normal + mirrored at 0 degrees
    string result = scanOrientation(frame);
    if (!result.empty()) return result;

    QImage unmirrored = frame.mirrored(true, false);
    result = scanOrientation(unmirrored);
    if (!result.empty()) return result;

    // 2. Handle slight hand tilt (-4 deg and +4 deg) when holding phone
    const double angles[] = { -4.0, 4.0 };
    for (double angle : angles) {
        QTransform rot;
        rot.rotate(angle);
        QImage r1 = frame.transformed(rot, Qt::SmoothTransformation);
        result = scanOrientation(r1);
        if (!result.empty()) return result;

        QImage r2 = unmirrored.transformed(rot, Qt::SmoothTransformation);
        result = scanOrientation(r2);
        if (!result.empty()) return result;
    }

    return "";
}

} // namespace

// ============================================================
//  Camera scan
// ============================================================
bool POSController::handleBarcodeScan(std::string& outBarcode, std::string& outMessage)
{
    outBarcode.clear();
    outMessage.clear();

    if (cameraHandler == nullptr || productManager == nullptr) {
        outMessage = "System is not initialized properly.";
        return false;
    }

    if (!cameraHandler->isCameraAvailable()) {
        if (!cameraHandler->initializeCamera()) {
            outMessage = "Camera is not available.";
            return false;
        }
    }
    if (!cameraHandler->checkCameraStatus()) {
        outMessage = "Camera is not ready.";
        return false;
    }

    QImage frame;
    if (cameraHandler->captureFrame()) {
        frame = cameraHandler->convertFrameToImageData();
    }
    if (frame.isNull()) {
        frame = cameraHandler->getCapturedImage();
    }
    if (frame.isNull()) {
        outMessage = "No camera image yet. Try again.";
        return false;
    }

    string decoded = decodeFrame(frame);
    if (decoded.empty()) {
        outMessage = "No barcode detected. Hold phone steady in front of camera.";
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

// ============================================================
//  Image file scan
// ============================================================
bool POSController::handleBarcodeScanFromImage(const std::string& imagePath, std::string& outBarcode, std::string& outMessage)
{
    outBarcode.clear();
    outMessage.clear();

    if (productManager == nullptr) {
        outMessage = "System is not initialized properly.";
        return false;
    }

    QImage img(QString::fromStdString(imagePath));
    if (img.isNull()) {
        outMessage = "Could not open the image file.";
        return false;
    }

    string decoded = decodeFrame(img);
    if (decoded.empty()) {
        outMessage = "Barcode could not be decoded from this image.";
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

// ============================================================
//  Barcode generation
// ============================================================
bool POSController::handleBarcodeGeneration(const std::string& digits, std::string& outFilePath, std::string& outMessage)
{
    outMessage.clear();

    if (digits.size() != 6) {
        outMessage = "Enter exactly six digits.";
        return false;
    }
    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] < '0' || digits[i] > '9') {
            outMessage = "The barcode may contain digits only.";
            return false;
        }
    }

    string pattern = BarcodeEncoder::encodeSixDigits(digits);
    if (pattern.empty()) {
        outMessage = "Could not encode this number.";
        return false;
    }

    bool onlyBits = true;
    for (size_t i = 0; i < pattern.size(); ++i) {
        if (pattern[i] != '0' && pattern[i] != '1') {
            onlyBits = false;
            break;
        }
    }
    if (!onlyBits) {
        pattern = BarcodeEncoder::widthsToModules(pattern);
        if (pattern.empty()) {
            outMessage = "Could not convert the encoded pattern.";
            return false;
        }
    }

    const int moduleWidth = 4;
    const int barHeight = 150;
    const int quietModules = 10;
    const int totalModules = static_cast<int>(pattern.size()) + 2 * quietModules;

    QImage img(totalModules * moduleWidth, barHeight, QImage::Format_RGB32);
    img.fill(Qt::white);
    for (size_t m = 0; m < pattern.size(); ++m) {
        if (pattern[m] != '1') continue;
        int x0 = (quietModules + static_cast<int>(m)) * moduleWidth;
        for (int dx = 0; dx < moduleWidth; ++dx)
            for (int y = 0; y < barHeight; ++y)
                img.setPixel(x0 + dx, y, qRgb(0, 0, 0));
    }

    if (outFilePath.empty()) {
        if (productManager != nullptr) {
            Product* p = productManager->findProductByBarcode(digits);
            if (p != nullptr && !p->getBarcodeFilePath().empty()) {
                outFilePath = p->getBarcodeFilePath();
            }
        }
        if (outFilePath.empty()) {
            outFilePath = string(POS_DATA_DIR) + "Barcodes/" + digits + ".bmp";
        }
    }

    QString qPath = QString::fromStdString(outFilePath);
    QFileInfo(qPath).dir().mkpath(".");
    if (!img.save(qPath, "BMP")) {
        outMessage = "Could not save the barcode image.";
        return false;
    }

    outMessage = "Barcode saved to " + outFilePath;
    return true;
}

// ============================================================
//  Product / order / bill / payment
// ============================================================
std::string POSController::handleProductDescription(const std::string& barcode) const
{
    if (productManager == nullptr || barcode.empty()) {
        return "";
    }
    return productManager->getProductDescription(barcode);
}

bool POSController::handleOrderRecording(const std::string& customerName, const std::string& customerContact, const std::string& barcode, int quantity)
{
    if (productManager == nullptr || orderManager == nullptr || orderFileHandler == nullptr) {
        return false;
    }
    if (barcode.empty() || quantity <= 0) {
        return false;
    }

    if (orderManager->getCurrentOrder().getOrderId().empty()) {
        if (customerName.empty() || !orderManager->createOrder(customerName, customerContact)) {
            return false;
        }
    }

    Product* product = productManager->findProductByBarcode(barcode);
    if (product == nullptr) {
        return false;
    }

    if (!productManager->checkAvailableQuantity(product->getProductId(), quantity)) {
        return false;
    }

    if (!orderManager->addProductToOrder(*product, quantity)) {
        return false;
    }

    if (!orderManager->validateOrder(*productManager)) {
        orderManager->removeProductFromOrder(product->getProductId());
        return false;
    }

    return orderFileHandler->saveOrder(orderManager->getCurrentOrder());
}

bool POSController::handleRemoveProduct(const std::string& barcode)
{
    if (productManager == nullptr || orderManager == nullptr || barcode.empty()) {
        return false;
    }

    Product* product = productManager->findProductByBarcode(barcode);
    if (product == nullptr) {
        return false;
    }

    return orderManager->removeProductFromOrder(product->getProductId());
}

Bill POSController::handleBillGeneration()
{
    if (productManager == nullptr || orderManager == nullptr ||
        billManager == nullptr || billFileHandler == nullptr) {
        return Bill();
    }
    if (orderManager->getDetailCount() == 0) {
        return Bill();
    }

    Bill bill = billManager->generateBill(orderManager->getCurrentOrder(),
                                          orderManager->getOrderDetails(),
                                          orderManager->getDetailCount(),
                                          *productManager);

    billFileHandler->saveBill(bill);
    return bill;
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
        return false;
    }

    const Bill& currentBill = billManager->getCurrentBill();
    const double payable = currentBill.getPayableAmount();
    if (payable <= 0.0) {
        return false;
    }

    if (!paymentManager->processPayment(amount, payable, mode, merchant)) {
        return false;
    }

    Order& order = orderManager->getCurrentOrder();
    order.setPaymentDetails(amount, mode, merchant);

    Bill paidBill = currentBill;
    paymentManager->updateOrderPaymentStatus(order, paidBill);

    const OrderDetail* details = orderManager->getOrderDetails();
    for (int i = 0; i < count; ++i) {
        productManager->deductStock(details[i].getProductId(), details[i].getQuantity());
    }

    bool ok = true;
    ok = orderFileHandler->saveOrder(order) && ok;
    ok = billFileHandler->saveBill(paidBill) && ok;
    ok = productFileHandler->saveProducts(productManager->getProducts(),
                                          productManager->getProductCount()) && ok;
    return ok;
}

// ============================================================
//  Getters for the GUI
// ============================================================
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