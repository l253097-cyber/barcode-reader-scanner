// PRE-WRITTEN by the team lead (Member 5 / integrator may extend it).
#include <QApplication>
#include "FileHandlers/ProductFileHandler.h"
#include "FileHandlers/OrderFileHandler.h"
#include "FileHandlers/BillFileHandler.h"
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

    // Modern White & Purple Theme
    app.setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #F6F3FC;
            color: #1F1933;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 14px;
        }

        /* Top Navigation Toolbar */
        QToolBar {
            background-color: #5E2CED;
            border: none;
            spacing: 10px;
            padding: 8px 16px;
        }
        QToolBar QToolButton {
            background-color: transparent;
            color: #FFFFFF;
            font-weight: bold;
            font-size: 14px;
            padding: 8px 16px;
            border-radius: 6px;
        }
        QToolBar QToolButton:hover {
            background-color: #774BF5;
        }
        QToolBar QToolButton:pressed {
            background-color: #481CC7;
        }

        /* White Card Containers */
        QFrame#CardContainer, QGroupBox {
            background-color: #FFFFFF;
            border: 1.5px solid #E3DAFA;
            border-radius: 16px;
        }

        QLabel {
            background-color: transparent;
            color: #261E42;
        }

        /* Primary Purple Buttons */
        QPushButton {
            background-color: #5E2CED;
            color: #FFFFFF;
            border: none;
            border-radius: 10px;
            padding: 12px 24px;
            font-weight: bold;
            font-size: 15px;
        }
        QPushButton:hover {
            background-color: #7245F5;
        }
        QPushButton:pressed {
            background-color: #461AB8;
        }
        QPushButton:disabled {
            background-color: #C9B9F7;
            color: #F4F0FE;
        }

        /* Input Boxes */
        QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {
            background-color: #FFFFFF;
            color: #1F1933;
            border: 1.5px solid #D3C4F7;
            border-radius: 8px;
            padding: 8px 12px;
            selection-background-color: #5E2CED;
        }
        QLineEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {
            border: 2px solid #5E2CED;
        }

        /* Bill / Receipt Display Area */
        QTextEdit, QPlainTextEdit {
            background-color: #FFFFFF;
            color: #1F1933;
            border: 2px solid #D3C4F7;
            border-radius: 12px;
            padding: 18px;
            font-family: 'Consolas', 'Courier New', monospace;
            font-size: 14px;
        }

        /* Tables */
        QTableWidget, QTableView {
            background-color: #FFFFFF;
            alternate-background-color: #F7F4FE;
            gridline-color: #E7DFFC;
            border: 1.5px solid #D3C4F7;
            border-radius: 10px;
        }
        QHeaderView::section {
            background-color: #5E2CED;
            color: #FFFFFF;
            font-weight: bold;
            padding: 8px;
            border: none;
        }

        /* Popups & Dialogs */
        QMessageBox, QInputDialog {
            background-color: #FFFFFF;
        }
    )");

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
    OrderFileHandler orderFile;
    BillFileHandler billFile;

    // 3. Controller = the only thing the GUI talks to
    POSController controller(&productManager, &orderManager, &billManager, &paymentManager,
                             &cameraHandler, &productFile, &orderFile, &billFile);

    // 4. GUI
    POSMainWindow window(&controller);
    window.show();
    return app.exec();
}