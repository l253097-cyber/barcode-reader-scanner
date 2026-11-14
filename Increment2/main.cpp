// PRE-WRITTEN by the team lead (Member 5 / integrator may extend it).
#include <QApplication>
#include "FileHandlers/ProductFileHandler.h"
#include "Managers/ProductManager.h"
#include "Managers/OrderManager.h"
#include "Managers/BillManager.h"
#include "Managers/PaymentManager.h"
#include "Camera/CameraHandler.h"
#include "POSController/POSController.h"
#include "MainWindow/POSMainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 1. Load products from Data/Product.txt into the ProductManager
    ProductFileHandler productFile;
    productFile.loadProducts();
    ProductManager productManager;
    productManager.setProducts(productFile.getProducts(), productFile.getProductCount());

    // 2. Other backend objects
    OrderManager orderManager;
    BillManager billManager;
    PaymentManager paymentManager;
    CameraHandler cameraHandler;

    // 3. Controller = the only thing the GUI talks to
    POSController controller(&productManager, &orderManager, &billManager, &paymentManager, &cameraHandler);

    // 4. GUI
    POSMainWindow window(&controller);
    window.show();
    return app.exec();
}
