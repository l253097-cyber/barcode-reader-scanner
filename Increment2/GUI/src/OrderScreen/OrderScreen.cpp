#include "OrderScreen/OrderScreen.h"

/*
 * ============================================================
 *  OrderScreen
 *  Order screen: customer info, order items table, add/remove/description/generate-bill.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 3 : setupOrderScreen(), displayOrderItems(), handleAddProduct(), handleQuantityInput(), handleGenerateBillButton() [EXTRA]
 *    Member 4 : handleDescriptionButton(), handleRemoveProduct()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

void OrderScreen::setupOrderScreen()
{
    // ===== MEMBER 3 : START =====
    // ---- setupOrderScreen ----
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Order");
    title->setStyleSheet("font-size: 18px; font-weight: bold;");
    mainLayout->addWidget(title);

    // customer info
    customerNameInput = new QLineEdit;
    customerNameInput->setPlaceholderText("Customer name");
    customerContactInput = new QLineEdit;
    customerContactInput->setPlaceholderText("Customer contact (phone)");
    QFormLayout* customerForm = new QFormLayout;
    customerForm->addRow("Name:", customerNameInput);
    customerForm->addRow("Contact:", customerContactInput);
    mainLayout->addLayout(customerForm);

    // order items table: column 0 holds the barcode (Member 4's remove/description use it)
    orderItemsTable = new QTableWidget(0, 4);
    orderItemsTable->setHorizontalHeaderLabels({ "Barcode", "Product", "Quantity", "Line Total" });
    orderItemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    orderItemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderItemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderItemsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(orderItemsTable);

    // quantity + buttons
    quantityInput = new QLineEdit;
    quantityInput->setPlaceholderText("Quantity");
    quantityInput->setText("1");
    quantityInput->setValidator(new QIntValidator(1, 999, this));     // only digits can be typed
    addProductButton = new QPushButton("Add Product");
    removeProductButton = new QPushButton("Remove Product");
    descriptionButton = new QPushButton("Product Description");
    generateBillButton = new QPushButton("Generate Bill");

    QHBoxLayout* buttonRow = new QHBoxLayout;
    buttonRow->addWidget(new QLabel("Qty:"));
    buttonRow->addWidget(quantityInput);
    buttonRow->addWidget(addProductButton);
    buttonRow->addWidget(removeProductButton);
    buttonRow->addWidget(descriptionButton);
    mainLayout->addLayout(buttonRow);
    mainLayout->addWidget(generateBillButton);

    connect(quantityInput, &QLineEdit::textChanged, this, &OrderScreen::handleQuantityInput);
    connect(addProductButton, &QPushButton::clicked, this, &OrderScreen::handleAddProduct);
    connect(removeProductButton, &QPushButton::clicked, this, &OrderScreen::handleRemoveProduct);          // Member 4's slot
    connect(descriptionButton, &QPushButton::clicked, this, &OrderScreen::handleDescriptionButton);        // Member 4's slot
    connect(generateBillButton, &QPushButton::clicked, this, &OrderScreen::handleGenerateBillButton);

    handleQuantityInput(quantityInput->text());                         // set the Add button's starting state
    // ===== MEMBER 3 : END =====
}

void OrderScreen::displayOrderItems(const OrderDetail* items, int count)
{
    // ===== MEMBER 3 : START =====
    // ---- displayOrderItems(const OrderDetail* items, int count) ----
    orderItemsTable->setRowCount(0);
    for (int i = 0; i < count; i++)
    {
        const std::string barcode = items[i].getProductBarcode();
        const Product* p = controller->findProductByBarcode(barcode);   // CHECK 1
        QString name = p ? QString::fromStdString(p->getProductName()) : QString("(unknown product)");
        double lineTotal = p ? p->getUnitPrice() * items[i].getQuantity() : 0.0;

        int row = orderItemsTable->rowCount();
        orderItemsTable->insertRow(row);
        orderItemsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(barcode)));
        orderItemsTable->setItem(row, 1, new QTableWidgetItem(name));
        orderItemsTable->setItem(row, 2, new QTableWidgetItem(QString::number(items[i].getQuantity())));
        orderItemsTable->setItem(row, 3, new QTableWidgetItem(QString::number(lineTotal, 'f', 2)));
    }
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleAddProduct()
{
    // ===== MEMBER 3 : START =====
  // ---- handleAddProduct ----
    bool ok = false;
    int quantity = quantityInput->text().trimmed().toInt(&ok);
    if (!ok || quantity < 1)
    {
        QMessageBox::warning(this, "Add Product", "Enter a quantity of 1 or more.");
        return;
    }

    const Product* product = controller->getScannedProduct();           // CHECK 1: the product the scanner found
    if (product == nullptr)
    {
        QMessageBox::warning(this, "Add Product", "Scan a product first.");
        return;
    }
    if (quantity > product->getAvailableQuantity())
    {
        QMessageBox::warning(this, "Add Product",
            QString("Not enough stock. Available: %1").arg(product->getAvailableQuantity()));
        return;
    }
    if (!controller->addProductToOrder(product->getBarcode(), quantity)) // CHECK 1
    {
        QMessageBox::warning(this, "Add Product", "Could not add this product to the order.");
        return;
    }

    quantityInput->setText("1");
    OrderDetail items[100];
    int count = controller->getOrderItems(items, 100);                  // CHECK 1
    displayOrderItems(items, count);
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleQuantityInput(const QString& text)
{
    // ===== MEMBER 3 : START =====
    // TODO: Validate that text is a positive whole number; disable Add button otherwise.
    // ---- handleQuantityInput(const QString& text) ----
    bool ok = false;
    int quantity = text.trimmed().toInt(&ok);
    bool valid = ok && quantity >= 1 && quantity <= 999;

    if (valid || text.isEmpty())
        quantityInput->setStyleSheet(QString());                        // normal look
    else
        quantityInput->setStyleSheet("border: 1px solid red;");         // red border for a bad value
    addProductButton->setEnabled(valid);                                // can't add with a bad quantity
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleDescriptionButton()
{
    // ===== MEMBER 4 : START =====
    // TODO: Get selected row's barcode, call controller->handleProductDescription(), send result to ProductDescriptionScreen and open it.
    
    // ===== MEMBER 4 : END =====
}

void OrderScreen::handleRemoveProduct()
{
    // ===== MEMBER 4 : START =====
    // TODO: Remove the selected row's product from the order, refresh the table.
    // ===== MEMBER 4 : END =====
}

void OrderScreen::handleGenerateBillButton()
{
    // ===== MEMBER 3 (EXTRA - not in the official final list) : START =====
    // TODO: Call controller->handleBillGeneration() and open the Bill screen.
   // ---- handleGenerateBillButton (EXTRA) ----
    QString name = customerNameInput->text().trimmed();
    QString contact = customerContactInput->text().trimmed();

    if (name.isEmpty())
    {
        QMessageBox::warning(this, "Generate Bill", "Enter the customer name.");
        customerNameInput->setFocus();
        return;
    }
    for (QChar c : contact)                                             // CHECK 2: contact rule is my guess
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
    if (!controller->generateBill(name.toStdString(), contact.toStdString()))   // CHECK 1
    {
        QMessageBox::warning(this, "Generate Bill", "Could not generate the bill.");
        return;
    }
    // TODO: ask MainWindow (Member 1) to show the Bill screen. Check how navigation is done there.
    // ===== MEMBER 3 (EXTRA - not in the official final list) : END =====
}
