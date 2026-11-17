#include "ProductDescriptionScreen/ProductDescriptionScreen.h"
#include <QFormLayout>
#include <QVBoxLayout>

/*
 * ============================================================
 *  ProductDescriptionScreen
 *  Product description screen (read-only product details).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 4 : setupProductDescriptionScreen(), displayProductDetails(), handleCloseDescription() [EXTRA]
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

void ProductDescriptionScreen::setupProductDescriptionScreen()
{
    // ===== MEMBER 4 : START =====
    setWindowTitle("Product Description");

    productNameLabel = new QLabel(this);
    barcodeLabel = new QLabel(this);
    priceLabel = new QLabel(this);
    unitLabel = new QLabel(this);
    stockLabel = new QLabel(this);
    taxLabel = new QLabel(this);
    discountLabel = new QLabel(this);
    closeButton = new QPushButton("Close", this);

    QFormLayout* form = new QFormLayout;
    form->addRow("Name:", productNameLabel);
    form->addRow("Barcode:", barcodeLabel);
    form->addRow("Price:", priceLabel);
    form->addRow("Unit:", unitLabel);
    form->addRow("Stock:", stockLabel);
    form->addRow("Tax:", taxLabel);
    form->addRow("Discount:", discountLabel);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(form);
    mainLayout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked,
        this, &ProductDescriptionScreen::handleCloseDescription);
    // ===== MEMBER 4 : END =====
}

void ProductDescriptionScreen::displayProductDetails(const Product& product)
{
    // ===== MEMBER 4 : START =====
    productNameLabel->setText(QString::fromStdString(product.getProductName()));
    barcodeLabel->setText(QString::fromStdString(product.getBarcode()));
    unitLabel->setText(QString::fromStdString(product.getMeasurementUnit()));
    priceLabel->setText(QString::number(product.getUnitPrice(), 'f', 2));
    taxLabel->setText(QString::number(product.getTax(), 'f', 2));
    discountLabel->setText(QString::number(product.getDiscount(), 'f', 2));
    stockLabel->setText(QString::number(product.getAvailableQuantity()));
    // ===== MEMBER 4 : END =====
}

void ProductDescriptionScreen::handleCloseDescription()
{
    // ===== MEMBER 4 (EXTRA - not in the official final list) : START =====
    close();
    // ===== MEMBER 4 (EXTRA - not in the official final list) : END =====
}