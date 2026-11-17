#include "BillScreen/BillScreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>
/*
 * ============================================================
 *  BillScreen
 *  Bill screen: bill details + payment (cash/card/wallet) + paid status.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 5 : setupBillScreen(), displayBillDetails(), handlePaymentInput(), handleConfirmPayment(), displayPaymentStatus() [EXTRA], handlePrintOrCloseBill() [EXTRA]
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

void BillScreen::setupBillScreen()
{
    // ===== MEMBER 5 : START =====
    // TODO: Create table, labels, combo box (Cash/Card/Wallet), inputs, buttons; layout; connect signals.
    setWindowTitle("Bill");

    // --- Items table ---
    billItemsTable = new QTableWidget(0, 5, this);
    billItemsTable->setHorizontalHeaderLabels({"Product", "Qty", "Unit Price", "Discount/Unit", "Subtotal"});
    billItemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    billItemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    billItemsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // --- Totals labels ---
    subtotalLabel      = new QLabel("Subtotal: 0.00", this);
    taxLabel           = new QLabel("Tax: 0.00", this);
    discountLabel      = new QLabel("Discount: 0.00", this);
    payableAmountLabel = new QLabel("Payable: 0.00", this);
    QFont f = payableAmountLabel->font();
    f.setBold(true);
    f.setPointSize(f.pointSize() + 2);
    payableAmountLabel->setFont(f);

    // --- Payment inputs ---
    paymentModeSelector = new QComboBox(this);
    paymentModeSelector->addItems({"Cash", "Card", "Wallet"});

    paymentAmountInput = new QLineEdit(this);
    paymentAmountInput->setPlaceholderText("Amount received");

    merchantInput = new QLineEdit(this);
    merchantInput->setPlaceholderText("Merchant / Card / Wallet name");
    merchantInput->setEnabled(false);   // Cash is the default mode

    paymentStatusLabel = new QLabel("Unpaid", this);
    paymentStatusLabel->setStyleSheet("color: red; font-weight: bold;");

    confirmPaymentButton = new QPushButton("Confirm Payment", this);
    confirmPaymentButton->setEnabled(false);

    printCloseButton = new QPushButton("Print / Close", this);

    // --- Layout ---
    QFormLayout* form = new QFormLayout();
    form->addRow("Payment Mode:", paymentModeSelector);
    form->addRow("Amount:", paymentAmountInput);
    form->addRow("Merchant:", merchantInput);

    QHBoxLayout* buttons = new QHBoxLayout();
    buttons->addStretch();
    buttons->addWidget(confirmPaymentButton);
    buttons->addWidget(printCloseButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(billItemsTable);
    mainLayout->addWidget(subtotalLabel);
    mainLayout->addWidget(taxLabel);
    mainLayout->addWidget(discountLabel);
    mainLayout->addWidget(payableAmountLabel);
    mainLayout->addLayout(form);
    mainLayout->addWidget(paymentStatusLabel);
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

    // One bill = one product line
    billItemsTable->setRowCount(0);
    billItemsTable->insertRow(0);
    billItemsTable->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(bill.getProductAcronym())));
    billItemsTable->setItem(0, 1, new QTableWidgetItem(QString::number(bill.getQuantity())));
    billItemsTable->setItem(0, 2, new QTableWidgetItem(QString::number(bill.getUnitPrice(), 'f', 2)));
    billItemsTable->setItem(0, 3, new QTableWidgetItem(QString::number(bill.getDiscountPerUnit(), 'f', 2)));
    billItemsTable->setItem(0, 4, new QTableWidgetItem(QString::number(bill.getSubtotal(), 'f', 2)));

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
    // TODO: Validate amount + merchant fields while the user types; enable/disable Confirm button.
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
    // TODO: Call controller->handlePayment(amount, mode, merchant); on success call displayPaymentStatus("Paid").
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
    // TODO: Show status (Paid / Unpaid / error) in paymentStatusLabel.
    paymentStatusLabel->setText(status);

    if (status.compare("Paid", Qt::CaseInsensitive) == 0)
        paymentStatusLabel->setStyleSheet("color: green; font-weight: bold;");
    else
        paymentStatusLabel->setStyleSheet("color: red; font-weight: bold;");
    // ===== MEMBER 5 (EXTRA - not in the official final list) : END =====
}

void BillScreen::handlePrintOrCloseBill()
{
    // ===== MEMBER 5 (EXTRA - not in the official final list) : START =====
    // TODO: Print or close the bill and go back to the dashboard.
    if (paymentStatusLabel->text() != "Paid") {
        auto reply = QMessageBox::question(this, "Bill not paid",
                                           "This bill is unpaid. Close anyway?");
        if (reply != QMessageBox::Yes)
            return;
    }
    // Closing this widget returns to the dashboard (which should be shown by the main window).
    close();
    // ===== MEMBER 5 (EXTRA - not in the official final list) : END =====
}
