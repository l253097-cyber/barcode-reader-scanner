// PRE-WRITTEN by the team lead (Member 5 / integrator may extend it).
#include <QApplication>
#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>

#include "Config.h"
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

namespace {

// Opens a White & Purple dialog allowing the store person to populate Product.txt when empty
void promptStorePersonToFillProducts(ProductFileHandler& productFile, ProductManager& productManager)
{
    QDialog dialog;
    dialog.setWindowTitle("Store Inventory Setup - Add Products");
    dialog.setMinimumSize(700, 520);

    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(24, 20, 24, 20);
    mainLayout->setSpacing(12);

    QLabel* title = new QLabel("Product.txt is Empty — Add Store Products");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold; color: #4A1FD1;");
    mainLayout->addWidget(title);

    QLabel* hint = new QLabel("Enter product details and click 'Add to Inventory'. Click 'Done & Open POS' when finished.");
    hint->setAlignment(Qt::AlignCenter);
    hint->setStyleSheet("color: #6E6299; font-size: 13px;");
    mainLayout->addWidget(hint);

    // Form inputs matching Product.txt 10 fields:
    // productId|barcode|acronym|name|unit|unitPrice|tax|discount|quantity|barcodeFilePath
    QLineEdit* idInput = new QLineEdit();
    idInput->setPlaceholderText("e.g. P001");

    QLineEdit* barcodeInput = new QLineEdit();
    barcodeInput->setPlaceholderText("6-digit non-zero start (e.g. 123456)");
    barcodeInput->setMaxLength(6);

    QLineEdit* acronymInput = new QLineEdit();
    acronymInput->setPlaceholderText("e.g. MILK");

    QLineEdit* nameInput = new QLineEdit();
    nameInput->setPlaceholderText("e.g. Organic Milk 1L");

    QLineEdit* unitInput = new QLineEdit();
    unitInput->setPlaceholderText("e.g. pcs, kg, L");
    unitInput->setText("pcs");

    QDoubleSpinBox* priceInput = new QDoubleSpinBox();
    priceInput->setRange(0.01, 999999.0);
    priceInput->setValue(100.00);

    QDoubleSpinBox* taxInput = new QDoubleSpinBox();
    taxInput->setRange(0.0, 100.0);
    taxInput->setValue(5.0);

    QDoubleSpinBox* discountInput = new QDoubleSpinBox();
    discountInput->setRange(0.0, 999999.0);
    discountInput->setValue(0.0);

    QSpinBox* stockInput = new QSpinBox();
    stockInput->setRange(1, 99999);
    stockInput->setValue(50);

    QFormLayout* form = new QFormLayout();
    form->setSpacing(8);
    form->addRow("Product ID:", idInput);
    form->addRow("6-Digit Barcode:", barcodeInput);
    form->addRow("Acronym:", acronymInput);
    form->addRow("Product Name:", nameInput);
    form->addRow("Unit:", unitInput);
    form->addRow("Unit Price:", priceInput);
    form->addRow("Tax (%):", taxInput);
    form->addRow("Discount / Unit:", discountInput);
    form->addRow("Quantity (Stock):", stockInput);
    mainLayout->addLayout(form);

    // Preview table of added products
    QTableWidget* addedTable = new QTableWidget(0, 5);
    addedTable->setHorizontalHeaderLabels({"ID", "Barcode", "Name", "Price", "Stock"});
    addedTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    addedTable->verticalHeader()->setVisible(false);
    addedTable->setMaximumHeight(130);
    mainLayout->addWidget(addedTable);

    QPushButton* addBtn = new QPushButton("Add to Inventory");
    QPushButton* doneBtn = new QPushButton("Done & Open POS");
    doneBtn->setStyleSheet(
        "QPushButton { background-color: #EDE6FE; color: #5E2CED; border: 1.5px solid #C8B5FA; }"
        "QPushButton:hover { background-color: #E0D4FD; }"
        );

    QHBoxLayout* btnRow = new QHBoxLayout();
    btnRow->addWidget(addBtn);
    btnRow->addWidget(doneBtn);
    mainLayout->addLayout(btnRow);

    QString productFilePath = QString(POS_DATA_DIR) + "Product.txt";

    QObject::connect(addBtn, &QPushButton::clicked, [&]() {
        QString id      = idInput->text().trimmed();
        QString barcode = barcodeInput->text().trimmed();
        QString acronym = acronymInput->text().trimmed();
        QString name    = nameInput->text().trimmed();
        QString unit    = unitInput->text().trimmed();

        if (id.isEmpty() || name.isEmpty() || acronym.isEmpty() || unit.isEmpty()
            || barcode.size() != 6 || barcode[0] == '0') {
            QMessageBox::warning(&dialog, "Invalid Input",
                                 "Fill all fields and enter a valid 6-digit barcode (cannot start with 0).");
            return;
        }
        for (QChar ch : barcode) {
            if (!ch.isDigit()) {
                QMessageBox::warning(&dialog, "Invalid Barcode", "Barcode must contain digits only.");
                return;
            }
        }

        QFileInfo(productFilePath).dir().mkpath(".");
        QFile file(productFilePath);
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::warning(&dialog, "File Error", "Could not open " + productFilePath);
            return;
        }

        QString barcodeImgPath = QString(POS_DATA_DIR) + "Barcodes/" + barcode + ".bmp";
        QTextStream out(&file);
        // Exact 10-field format: productId|barcode|acronym|name|unit|unitPrice|tax|discount|quantity|barcodeFilePath
        out << id << "|"
            << barcode << "|"
            << acronym << "|"
            << name << "|"
            << unit << "|"
            << QString::number(priceInput->value(), 'f', 2) << "|"
            << QString::number(taxInput->value(), 'f', 2) << "|"
            << QString::number(discountInput->value(), 'f', 2) << "|"
            << stockInput->value() << "|"
            << barcodeImgPath << "\n";
        file.close();

        int row = addedTable->rowCount();
        addedTable->insertRow(row);
        addedTable->setItem(row, 0, new QTableWidgetItem(id));
        addedTable->setItem(row, 1, new QTableWidgetItem(barcode));
        addedTable->setItem(row, 2, new QTableWidgetItem(name));
        addedTable->setItem(row, 3, new QTableWidgetItem(QString::number(priceInput->value(), 'f', 2)));
        addedTable->setItem(row, 4, new QTableWidgetItem(QString::number(stockInput->value())));

        idInput->clear();
        barcodeInput->clear();
        acronymInput->clear();
        nameInput->clear();
        idInput->setFocus();
    });

    QObject::connect(doneBtn, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();

    // Reload Product.txt into ProductManager after user finishes adding items
    productFile.loadProducts();
    productManager.setProducts(productFile.getProducts(), productFile.getProductCount());
}

} // namespace

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Modern White & Purple Theme
    app.setStyleSheet(R"(
        QMainWindow, QWidget, QDialog {
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

        /* Dropdown Popup Menu & Scrollbars */
        QComboBox QAbstractItemView {
            background-color: #FFFFFF;
            color: #1F1933;
            border: 1.5px solid #5E2CED;
            selection-background-color: #5E2CED;
            selection-color: #FFFFFF;
            outline: 0;
        }
        QScrollBar:vertical {
            background: #F4EFFE;
            width: 8px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #B39DF7;
            border-radius: 4px;
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

    // If Product.txt is empty or missing, let the store person add products before opening POS
    if (productManager.getProductCount() == 0) {
        promptStorePersonToFillProducts(productFile, productManager);
    }

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