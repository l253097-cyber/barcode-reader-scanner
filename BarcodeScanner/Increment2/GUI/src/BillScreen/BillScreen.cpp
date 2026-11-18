#include "BillScreen/BillScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QFrame>
#include <QLabel>

/*
- ============================================================
-  BillScreen
-  Bill screen: bill details + payment (cash/card/wallet) + paid status.
- ------------------------------------------------------------
-  WHO WRITES WHAT (function ownership):
-    Member 5 : setupBillScreen(), displayBillDetails(), handlePaymentInput(), handleConfirmPayment(), displayPaymentStatus() [EXTRA], handlePrintOrCloseBill() [EXTRA]
-  Pre-written (getters/constructors): already done, don't touch.
-  Rule: only edit the function bodies marked with YOUR member number.
- ============================================================
 */

void BillScreen::setupBillScreen()
{
    // ===== MEMBER 5 : START =====
    setWindowTitle("Bill");

    // --- Centered Title Header ---
    QLabel* headerLabel = new QLabel("Customer Invoice & Payment", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    headerLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #4A1FD1; margin-bottom: 4px;");

    // --- Items table (centered cells) ---
    billItemsTable = new QTableWidget(0, 5, this);
    billItemsTable->setHorizontalHeaderLabels({"Product", "Qty", "Unit Price", "Discount/Unit", "Subtotal"});
    billItemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    billItemsTable->verticalHeader()->setVisible(false);
    billItemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    billItemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    billItemsTable->setMaximumHeight(140);
    billItemsTable->setAlternatingRowColors(true);

    // --- Centered Totals Card ---
    QFrame* totalsCard = new QFrame(this);
    totalsCard->setStyleSheet(
        "QFrame { background-color: #F4EFFE; border: 1.5px solid #D5C4FA; border-radius: 12px; padding: 10px; }"
        );
    totalsCard->setMaximumWidth(460);

    subtotalLabel      = new QLabel("Subtotal: 0.00", totalsCard);
    taxLabel           = new QLabel("Tax: 0.00", totalsCard);
    discountLabel      = new QLabel("Discount: 0.00", totalsCard);
    payableAmountLabel = new QLabel("Payable: 0.00", totalsCard);

    for (QLabel* lbl : { subtotalLabel, taxLabel, discountLabel, payableAmountLabel }) {
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setStyleSheet("background: transparent; border: none; color: #2D2254; font-size: 14px;");
    }

    payableAmountLabel->setStyleSheet(
        "background: transparent; border: none; color: #4A1FD1; font-size: 18px; font-weight: bold; margin-top: 4px;"
        );

    QVBoxLayout* totalsLayout = new QVBoxLayout(totalsCard);
    totalsLayout->setSpacing(4);
    totalsLayout->setAlignment(Qt::AlignCenter);
    totalsLayout->addWidget(subtotalLabel);
    totalsLayout->addWidget(taxLabel);
    totalsLayout->addWidget(discountLabel);
    totalsLayout->addWidget(payableAmountLabel);

    // --- Centered Payment Inputs ---
    paymentModeSelector = new QComboBox(this);
    paymentModeSelector->addItems({"Cash", "Card", "Wallet"});
    paymentModeSelector->setMinimumWidth(220);

    paymentAmountInput = new QLineEdit(this);
    paymentAmountInput->setPlaceholderText("Amount received");
    paymentAmountInput->setAlignment(Qt::AlignCenter);
    paymentAmountInput->setMinimumWidth(220);

    merchantInput = new QLineEdit(this);
    merchantInput->setPlaceholderText("Merchant / Card / Wallet name");
    merchantInput->setAlignment(Qt::AlignCenter);
    merchantInput->setMinimumWidth(220);
    merchantInput->setEnabled(false);   // Cash is the default mode

    paymentStatusLabel = new QLabel("Unpaid", this);
    paymentStatusLabel->setAlignment(Qt::AlignCenter);
    paymentStatusLabel->setStyleSheet("color: #D93025; font-weight: bold; font-size: 15px;");

    confirmPaymentButton = new QPushButton("Confirm Payment", this);
    confirmPaymentButton->setEnabled(false);
    confirmPaymentButton->setMinimumWidth(170);

    printCloseButton = new QPushButton("Print / Close", this);
    printCloseButton->setMinimumWidth(150);
    printCloseButton->setStyleSheet(
        "QPushButton { background-color: #EDE6FE; color: #5E2CED; border: 1.5px solid #C8B5FA; }"
        "QPushButton:hover { background-color: #E0D4FD; }"
        "QPushButton:pressed { background-color: #D0BEFC; }"
        );

    // --- Centered Form Container ---
    QWidget* formContainer = new QWidget(this);
    formContainer->setStyleSheet("background: transparent;");
    formContainer->setMaximumWidth(420);

    QFormLayout* form = new QFormLayout(formContainer);
    form->setFormAlignment(Qt::AlignCenter);
    form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    form->setSpacing(10);
    form->addRow("Payment Mode:", paymentModeSelector);
    form->addRow("Amount:", paymentAmountInput);
    form->addRow("Merchant:", merchantInput);

    // --- Centered Action Buttons ---
    QHBoxLayout* buttons = new QHBoxLayout();
    buttons->setAlignment(Qt::AlignCenter);
    buttons->setSpacing(14);
    buttons->addWidget(confirmPaymentButton);
    buttons->addWidget(printCloseButton);

    // --- Main Centered Layout ---
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(14);
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(billItemsTable);
    mainLayout->addWidget(totalsCard, 0, Qt::AlignHCenter);
    mainLayout->addWidget(formContainer, 0, Qt::AlignHCenter);
    mainLayout->addWidget(paymentStatusLabel, 0, Qt::AlignHCenter);
    mainLayout->addLayout(buttons);
    setLayout(mainLayout);

    // --- Signals ---
    connect(paymentAmountInput, &QLineEdit::textChanged, this, &BillScreen::handlePaymentInput);
    connect(merchantInput, &QLineEdit::textChanged, this, &BillScreen::handlePaymentInput);
    connect(paymentModeSelector, &QComboBox::currentTextChanged, this, &BillScreen::handlePaymentInput);
    connect(confirmPaymentButton, &QPushButton::clicked, this, &BillScreen::handleConfirmPayment);
    connect(printCloseButton, &QPushButton::clicked, this, &BillScreen::handlePrintOrCloseBill);
    // ===== MEMBER 5 : END =====
}

void BillScreen::displayBillDetails(const Bill& bill)
{
    // ===== MEMBER 5 : START =====
    setWindowTitle(QString("Bill %1 - %2")
                       .arg(QString::fromStdString(bill.getBillId()),
                            QString::fromStdString(bill.getCustomerName())));

    // One bill = one product line (with centered cell alignment)
    billItemsTable->setRowCount(0);
    billItemsTable->insertRow(0);

    QStringList rowValues = {
        QString::fromStdString(bill.getProductAcronym()),
        QString::number(bill.getQuantity()),
        QString::number(bill.getUnitPrice(), 'f', 2),
        QString::number(bill.getDiscountPerUnit(), 'f', 2),
        QString::number(bill.getSubtotal(), 'f', 2)
    };

    for (int col = 0; col < rowValues.size(); ++col) {
        QTableWidgetItem* item = new QTableWidgetItem(rowValues[col]);
        item->setTextAlignment(Qt::AlignCenter);
        billItemsTable->setItem(0, col, item);
    }

    subtotalLabel->setText("Subtotal: " + QString::number(bill.getSubtotal(), 'f', 2));
    taxLabel->setText("Tax: " + QString::number(bill.getTotalTax(), 'f', 2));
    discountLabel->setText("Discount: " + QString::number(bill.getTotalDiscount(), 'f', 2));
    payableAmountLabel->setText("Payable: " + QString::number(bill.getPayableAmount(), 'f', 2));

    // Store payable amount (no header change needed) for validation later
    setProperty("payableAmount", bill.getPayableAmount());

    // Reset payment inputs for this bill
    paymentAmountInput->clear();
    merchantInput->clear();
    paymentAmountInput->setEnabled(true);
    paymentModeSelector->setEnabled(true);

    QString status = QString::fromStdString(bill.getPaymentStatus());
    bool alreadyPaid = (status.compare("Paid", Qt::CaseInsensitive) == 0);
    displayPaymentStatus(alreadyPaid ? "Paid" : "Unpaid");

    if (alreadyPaid) {
        paymentAmountInput->setEnabled(false);
        paymentModeSelector->setEnabled(false);
        merchantInput->setEnabled(false);
        confirmPaymentButton->setEnabled(false);
    } else {
        handlePaymentInput();
    }
    // ===== MEMBER 5 : END =====
}

void BillScreen::handlePaymentInput()
{
    // ===== MEMBER 5 : START =====
    // Merchant is only needed for Card / Wallet
    bool needsMerchant = (paymentModeSelector->currentText() != "Cash");
    merchantInput->setEnabled(needsMerchant);
    if (!needsMerchant)
        merchantInput->clear();

    bool ok = false;
    double amount = paymentAmountInput->text().trimmed().toDouble(&ok);
    double payable = property("payableAmount").toDouble();

    bool amountValid = ok && amount > 0 && amount >= payable;
    bool merchantValid = !needsMerchant || !merchantInput->text().trimmed().isEmpty();

    confirmPaymentButton->setEnabled(amountValid && merchantValid);
    // ===== MEMBER 5 : END =====
}

void BillScreen::handleConfirmPayment()
{
    // ===== MEMBER 5 : START =====
    bool ok = false;
    double amount = paymentAmountInput->text().trimmed().toDouble(&ok);
    if (!ok || amount <= 0) {
        displayPaymentStatus("Error: invalid amount");
        return;
    }

    QString mode = paymentModeSelector->currentText();
    QString merchant = merchantInput->text().trimmed();

    if (controller && controller->handlePayment(amount, mode.toStdString(), merchant.toStdString())) {
        displayPaymentStatus("Paid");
        confirmPaymentButton->setEnabled(false);
        paymentAmountInput->setEnabled(false);
        merchantInput->setEnabled(false);
        paymentModeSelector->setEnabled(false);
    } else {
        displayPaymentStatus("Error: payment failed");
    }
    // ===== MEMBER 5 : END =====
}

void BillScreen::displayPaymentStatus(const QString& status)
{
    // ===== MEMBER 5 (EXTRA - not in the official final list) : START =====
    paymentStatusLabel->setText(status);

    if (status.compare("Paid", Qt::CaseInsensitive) == 0)
        paymentStatusLabel->setStyleSheet("color: #1E8E3E; font-weight: bold; font-size: 16px;");
    else
        paymentStatusLabel->setStyleSheet("color: #D93025; font-weight: bold; font-size: 15px;");
    // ===== MEMBER 5 (EXTRA - not in the official final list) : END =====
}

void BillScreen::handlePrintOrCloseBill()
{
    // ===== MEMBER 5 (EXTRA - not in the official final list) : START =====
    if (paymentStatusLabel->text() != "Paid") {
        auto reply = QMessageBox::question(this, "Bill not paid",
                                           "This bill is unpaid. Close anyway?");
        if (reply != QMessageBox::Yes)
            return;
    }
    QMessageBox::information(this, "Bill Closed", "Use the top Navigation bar to return to Dashboard or start a new order.");
    // ===== MEMBER 5 (EXTRA - not in the official final list) : END =====
}