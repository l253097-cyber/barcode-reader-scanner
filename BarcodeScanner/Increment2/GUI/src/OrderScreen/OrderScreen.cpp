#include "OrderScreen/OrderScreen.h"
#include "MainWindow/POSMainWindow.h"
#include "BillScreen/BillScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QIntValidator>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>

namespace {
QLineEdit* barcodeInputField = nullptr;
}

void OrderScreen::setupOrderScreen()
{
    // ===== MEMBER 3 : START =====
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(14);

    QLabel* title = new QLabel("Record Customer Order", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #4A1FD1; margin-bottom: 4px;");
    mainLayout->addWidget(title);

    // Centered Customer Info Form
    QWidget* formContainer = new QWidget(this);
    formContainer->setStyleSheet("background: transparent;");
    formContainer->setMaximumWidth(460);

    customerNameInput = new QLineEdit(formContainer);
    customerNameInput->setPlaceholderText("Enter customer name");
    customerNameInput->setMinimumWidth(260);

    customerContactInput = new QLineEdit(formContainer);
    customerContactInput->setPlaceholderText("Enter phone (e.g. 03001234567)");
    customerContactInput->setMinimumWidth(260);

    QFormLayout* customerForm = new QFormLayout(formContainer);
    customerForm->setFormAlignment(Qt::AlignCenter);
    customerForm->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    customerForm->setSpacing(10);
    customerForm->addRow("Customer Name:", customerNameInput);
    customerForm->addRow("Contact:", customerContactInput);
    mainLayout->addWidget(formContainer, 0, Qt::AlignHCenter);

    // Order Items Table
    orderItemsTable = new QTableWidget(0, 4, this);
    orderItemsTable->setHorizontalHeaderLabels({ "Barcode", "Product", "Quantity", "Line Total" });
    orderItemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    orderItemsTable->verticalHeader()->setVisible(false);
    orderItemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderItemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderItemsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    orderItemsTable->setAlternatingRowColors(true);
    orderItemsTable->setMinimumHeight(160);
    mainLayout->addWidget(orderItemsTable);

    // Product Barcode + Quantity Row
    barcodeInputField = new QLineEdit(this);
    barcodeInputField->setPlaceholderText("6-digit Barcode");
    barcodeInputField->setMaxLength(6);
    barcodeInputField->setAlignment(Qt::AlignCenter);
    barcodeInputField->setMaximumWidth(160);

    quantityInput = new QLineEdit(this);
    quantityInput->setPlaceholderText("Qty");
    quantityInput->setText("1");
    quantityInput->setAlignment(Qt::AlignCenter);
    quantityInput->setMaximumWidth(75);
    quantityInput->setValidator(new QIntValidator(1, 999, this));

    addProductButton = new QPushButton("Add Product", this);
    removeProductButton = new QPushButton("Remove", this);
    descriptionButton = new QPushButton("Description", this);

    QString secondaryStyle =
        "QPushButton { background-color: #EDE6FE; color: #5E2CED; border: 1.5px solid #C8B5FA; border-radius: 8px; padding: 10px 16px; font-weight: bold; }"
        "QPushButton:hover { background-color: #E0D4FD; }";
    removeProductButton->setStyleSheet(secondaryStyle);
    descriptionButton->setStyleSheet(secondaryStyle);

    QHBoxLayout* buttonRow = new QHBoxLayout();
    buttonRow->setAlignment(Qt::AlignCenter);
    buttonRow->setSpacing(10);
    buttonRow->addWidget(new QLabel("Barcode:", this));
    buttonRow->addWidget(barcodeInputField);
    buttonRow->addWidget(new QLabel("Qty:", this));
    buttonRow->addWidget(quantityInput);
    buttonRow->addWidget(addProductButton);
    buttonRow->addWidget(removeProductButton);
    buttonRow->addWidget(descriptionButton);
    mainLayout->addLayout(buttonRow);

    // Centered Generate Bill Action Button
    generateBillButton = new QPushButton("Generate Bill", this);
    generateBillButton->setMinimumSize(260, 48);
    generateBillButton->setMaximumWidth(300);
    mainLayout->addWidget(generateBillButton, 0, Qt::AlignHCenter);

    connect(quantityInput, &QLineEdit::textChanged, this, &OrderScreen::handleQuantityInput);
    connect(addProductButton, &QPushButton::clicked, this, &OrderScreen::handleAddProduct);
    connect(removeProductButton, &QPushButton::clicked, this, &OrderScreen::handleRemoveProduct);
    connect(descriptionButton, &QPushButton::clicked, this, &OrderScreen::handleDescriptionButton);
    connect(generateBillButton, &QPushButton::clicked, this, &OrderScreen::handleGenerateBillButton);

    handleQuantityInput(quantityInput->text());
    // ===== MEMBER 3 : END =====
}

void OrderScreen::displayOrderItems(const OrderDetail* items, int count)
{
    // ===== MEMBER 3 : START =====
    orderItemsTable->setRowCount(0);
    if (items == nullptr) return;

    for (int i = 0; i < count; i++)
    {
        const std::string barcode = items[i].getProductBarcode();
        std::string desc = controller ? controller->handleProductDescription(barcode) : "";
        QString productLabel = desc.empty()
                                   ? QString::fromStdString(barcode)
                                   : QString::fromStdString(desc);

        int row = orderItemsTable->rowCount();
        orderItemsTable->insertRow(row);

        QTableWidgetItem* c0 = new QTableWidgetItem(QString::fromStdString(barcode));
        QTableWidgetItem* c1 = new QTableWidgetItem(productLabel);
        QTableWidgetItem* c2 = new QTableWidgetItem(QString::number(items[i].getQuantity()));
        QTableWidgetItem* c3 = new QTableWidgetItem("Added");

        for (QTableWidgetItem* cell : { c0, c1, c2, c3 })
            cell->setTextAlignment(Qt::AlignCenter);

        orderItemsTable->setItem(row, 0, c0);
        orderItemsTable->setItem(row, 1, c1);
        orderItemsTable->setItem(row, 2, c2);
        orderItemsTable->setItem(row, 3, c3);
    }
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleAddProduct()
{
    // ===== MEMBER 3 : START =====
    bool ok = false;
    int quantity = quantityInput->text().trimmed().toInt(&ok);
    if (!ok || quantity < 1)
    {
        QMessageBox::warning(this, "Add Product", "Enter a quantity of 1 or more.");
        return;
    }

    QString name = customerNameInput->text().trimmed();
    QString contact = customerContactInput->text().trimmed();
    if (name.isEmpty())
    {
        QMessageBox::warning(this, "Add Product", "Enter the customer name first.");
        customerNameInput->setFocus();
        return;
    }

    std::string barcode = barcodeInputField ? barcodeInputField->text().trimmed().toStdString() : "";
    if (barcode.empty())
    {
        int currentRow = orderItemsTable->currentRow();
        if (currentRow >= 0 && orderItemsTable->item(currentRow, 0) != nullptr)
        {
            barcode = orderItemsTable->item(currentRow, 0)->text().toStdString();
        }
    }

    if (barcode.empty())
    {
        QMessageBox::warning(this, "Add Product", "Enter a 6-digit product barcode first.");
        if (barcodeInputField) barcodeInputField->setFocus();
        return;
    }

    if (!controller->handleOrderRecording(name.toStdString(), contact.toStdString(), barcode, quantity))
    {
        QMessageBox::warning(this, "Add Product",
                             "Could not add product.\nCheck that the 6-digit barcode exists in Product.txt and has enough stock.");
        return;
    }

    displayOrderItems(controller->getOrderItems(), controller->getOrderItemCount());

    if (barcodeInputField) barcodeInputField->clear();
    quantityInput->setText("1");
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleQuantityInput(const QString& text)
{
    // ===== MEMBER 3 : START =====
    bool ok = false;
    int quantity = text.trimmed().toInt(&ok);
    bool valid = ok && quantity >= 1 && quantity <= 999;

    if (valid || text.isEmpty())
        quantityInput->setStyleSheet(QString());
    else
        quantityInput->setStyleSheet("border: 2px solid #D93025;");
    addProductButton->setEnabled(valid);
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleDescriptionButton()
{
    // ===== MEMBER 4 : START =====
    int row = orderItemsTable->currentRow();
    std::string barcode = "";

    if (row >= 0 && orderItemsTable->item(row, 0) != nullptr)
        barcode = orderItemsTable->item(row, 0)->text().toStdString();
    else if (barcodeInputField && !barcodeInputField->text().trimmed().isEmpty())
        barcode = barcodeInputField->text().trimmed().toStdString();

    if (barcode.empty())
    {
        QMessageBox::warning(this, "Description", "Please select a product row or enter a barcode first.");
        return;
    }

    std::string description = controller->handleProductDescription(barcode);
    if (description.empty())
    {
        QMessageBox::warning(this, "Description", "Product details not found.");
        return;
    }

    QMessageBox::information(this, "Product Description", QString::fromStdString(description));
    // ===== MEMBER 4 : END =====
}

void OrderScreen::handleRemoveProduct()
{
    // ===== MEMBER 4 : START =====
    int row = orderItemsTable->currentRow();
    if (row < 0 || orderItemsTable->item(row, 0) == nullptr)
    {
        QMessageBox::warning(this, "Remove", "Please select a product row first.");
        return;
    }
    std::string barcode = orderItemsTable->item(row, 0)->text().toStdString();

    if (controller->handleRemoveProduct(barcode))
        displayOrderItems(controller->getOrderItems(), controller->getOrderItemCount());
    else
        QMessageBox::warning(this, "Remove", "Could not remove the product.");
    // ===== MEMBER 4 : END =====
}

void OrderScreen::handleGenerateBillButton()
{
    // ===== MEMBER 3 (EXTRA - not in the official final list) : START =====
    QString name = customerNameInput->text().trimmed();
    const QString contact = customerContactInput->text().trimmed();

    if (name.isEmpty())
    {
        QMessageBox::warning(this, "Generate Bill", "Enter the customer name.");
        customerNameInput->setFocus();
        return;
    }
    for (QChar c : contact)
    {
        if (!(c.isDigit() || c == QLatin1Char('+') || c == QLatin1Char('-') || c == QLatin1Char(' ')))
        {
            QMessageBox::warning(this, "Generate Bill", "The contact may only contain digits, +, - and spaces.");
            customerContactInput->setFocus();
            return;
        }
    }
    if (orderItemsTable->rowCount() == 0)
    {
        QMessageBox::warning(this, "Generate Bill", "Add at least one product first.");
        return;
    }

    Bill bill = controller->handleBillGeneration();
    if (bill.getBillId().empty())
    {
        QMessageBox::warning(this, "Generate Bill", "Could not generate bill for this order.");
        return;
    }

    if (auto* mainWin = qobject_cast<POSMainWindow*>(window()))
    {
        mainWin->handleBillNavigation();
    }
    // ===== MEMBER 3 (EXTRA - not in the official final list) : END =====
}