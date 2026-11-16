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
  
    // ===== MEMBER 3 : END =====
}

void OrderScreen::handleQuantityInput(const QString& text)
{
    // ===== MEMBER 3 : START =====
    // TODO: Validate that text is a positive whole number; disable Add button otherwise.
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
    // ===== MEMBER 3 (EXTRA - not in the official final list) : END =====
}
