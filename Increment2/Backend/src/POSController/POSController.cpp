#include "POSController/POSController.h"
#include "FileHandlers/ProductFileHandler.h"
#include "FileHandlers/OrderFileHandler.h"
#include "FileHandlers/OrderDetailFileHandler.h"
#include "FileHandlers/BillFileHandler.h"
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
        // Camera se tasveer lo, usme se barcode padho, phir product dhundo.
    outBarcode = "";
    outMessage = "";

    // 1) Camera chal raha hai?
    if (cameraHandler == nullptr || cameraHandler->checkCameraStatus() == false)
    {
        outMessage = "Camera is not running";
        return false;
    }

    // 2) Tasveer kheencho
    if (cameraHandler->captureFrame() == false)
    {
        outMessage = "Could not capture image";
        return false;
    }

    // 3) Tasveer ko image data me badlo
    QImage image = cameraHandler->convertFrameToImageData();
    if (image.isNull())
    {
        outMessage = "Image not ready, press Capture again";
        return false;
    }

    // 4) ===== YAHAN INCREMENT 1 KA DECODER CHALEGA =====
    // Image se barcode ka text nikalna hai (BarcodeScanner / BarcodeDecoder).
    // Is jagah ka code mujhe tab milega jab tum un files ke function names bhejogi.
    std::string barcode = "";

    if (barcode == "")
    {
        outMessage = "Barcode could not be read";
        return false;
    }
    outBarcode = barcode;

    // 5) Product dhundo
    Product* product = productManager->findProductByBarcode(barcode);
    if (product == nullptr)
    {
        outMessage = "Product not found";
        return false;
    }

    outMessage = product->getProductName() + " - Price: " + std::to_string(product->getUnitPrice());
    return true;
    // ===== MEMBER 5 : END =====
}

std::string POSController::handleProductDescription(const std::string& barcode) const
{
    // ===== MEMBER 5 : START =====
            // Product ki detail ka text manager se maango.
    if (productManager == nullptr)
    {
        return "Product manager not available";
    }
    return productManager->getProductDescription(barcode);
    // ===== MEMBER 5 : END =====
}

bool POSController::handleOrderRecording(const std::string& customerName, const std::string& customerContact, const std::string& barcode, int quantity)
{
    // ===== MEMBER 5 : START =====
        // Product ko order me daalo. Zaroorat ho to naya order bhi banao.
    // 1) Product dhundo
    Product* product = productManager->findProductByBarcode(barcode);
    if (product == nullptr)
    {
        return false;
    }

    // 2) Naya order chahiye? (koi order nahi, ya paise ho chuke, ya customer badal gaya)
    Order& current = orderManager->getCurrentOrder();
    if (current.getOrderId() == "" || current.getOrderStatus() != "Pending" || current.getCustomerName() != customerName)
    {
        if (orderManager->createOrder(customerName, customerContact) == false)
        {
            return false;
        }
    }

    // 3) Order me ye product pehle se kitna hai?
    int existing = 0;
    const OrderDetail* items = orderManager->getOrderDetails();
    for (int i = 0; i < orderManager->getDetailCount(); i++)
    {
        if (items[i].getProductId() == product->getProductId())
        {
            existing = items[i].getQuantity();
        }
    }

    // 4) Pehle wali + nayi quantity stock se zyada na ho
    if (productManager->checkAvailableQuantity(product->getProductId(), existing + quantity) == false)
    {
        return false;
    }

    // 5) Order me daalo
    return orderManager->addProductToOrder(*product, quantity);
    // ===== MEMBER 5 : END =====
}

Bill POSController::handleBillGeneration()
{
    // ===== MEMBER 5 : START =====
        // Order sahi hai to bill banao, warna khali Bill wapas do.
    // (GUI check karegi: bill.getBillId() == "" matlab bill nahi bana)
    if (orderManager->validateOrder(*productManager) == false)
    {
        return Bill();
    }

    return billManager->generateBill(orderManager->getCurrentOrder(),
        orderManager->getOrderDetails(),
        orderManager->getDetailCount(),
        *productManager);
    // ===== MEMBER 5 : END =====
}

bool POSController::handlePayment(double amount, const std::string& mode, const std::string& merchant)
{
    // ===== MEMBER 5 : START =====
        // Payment lo, stock kam karo, aur sab files me save karo.
    // 1) Bill maujood hai?
    Bill bill = billManager->getCurrentBill();
    if (bill.getBillId() == "")
    {
        return false;
    }

    // 2) Payment sahi hai? (PaymentManager check karega)
    if (paymentManager->processPayment(amount, bill.getPayableAmount(), mode, merchant) == false)
    {
        return false;
    }

    // 3) Order aur bill ka status "Paid" karo
    Order& order = orderManager->getCurrentOrder();
    paymentManager->updateOrderPaymentStatus(order, bill);

    // 4) Har item ka stock kam karo
    const OrderDetail* items = orderManager->getOrderDetails();
    for (int i = 0; i < orderManager->getDetailCount(); i++)
    {
        productManager->deductStock(items[i].getProductId(), items[i].getQuantity());
    }

    // 5) Sab files me save karo
    ProductFileHandler productFile;
    productFile.saveProducts(productManager->getProducts(), productManager->getProductCount());

    OrderFileHandler orderFile;
    orderFile.saveOrder(order);

    OrderDetailFileHandler detailFile;
    detailFile.saveOrderDetails(orderManager->getOrderDetails(), orderManager->getDetailCount());

    BillFileHandler billFile;
    billFile.saveBill(bill);

    return true;
    // ===== MEMBER 5 : END =====
}
bool POSController::handleProductDetails(const std::string& barcode, Product& outProduct) const
{
    if (productManager == nullptr)
    {
        return false;
    }

    Product* product = productManager->findProductByBarcode(barcode);
    if (product == nullptr)
    {
        return false;   // product nahi mila
    }

    outProduct = *product;
    return true;
}

bool POSController::handleRemoveProduct(const std::string& barcode)
{
    if (productManager == nullptr || orderManager == nullptr)
    {
        return false;
    }

    Product* product = productManager->findProductByBarcode(barcode);
    if (product == nullptr)
    {
        return false;   // product nahi mila
    }

    return orderManager->removeProductFromOrder(product->getProductId());
}