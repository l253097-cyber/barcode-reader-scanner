#ifndef BILLSCREEN_H
#define BILLSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QString>
#include "Models/Bill.h"
#include "POSController/POSController.h"

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

class BillScreen : public QWidget {
    Q_OBJECT
private:
    QTableWidget* billItemsTable = nullptr;
    QLabel* subtotalLabel = nullptr;
    QLabel* taxLabel = nullptr;
    QLabel* discountLabel = nullptr;
    QLabel* payableAmountLabel = nullptr;
    QComboBox* paymentModeSelector = nullptr;
    QLineEdit* paymentAmountInput = nullptr;
    QLineEdit* merchantInput = nullptr;
    QLabel* paymentStatusLabel = nullptr;
    QPushButton* confirmPaymentButton = nullptr;
    QPushButton* printCloseButton = nullptr;
    POSController* controller = nullptr;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    explicit BillScreen(POSController* controller, QWidget* parent = nullptr)
        : QWidget(parent), controller(controller) { setupBillScreen(); }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    void setupBillScreen();   // Member 5
    void displayBillDetails(const Bill& bill);   // Member 5
    void displayPaymentStatus(const QString& status);   // Member 5 (EXTRA)

public slots:
    void handlePaymentInput();   // Member 5
    void handleConfirmPayment();   // Member 5
    void handlePrintOrCloseBill();   // Member 5 (EXTRA)
};

#endif // BILLSCREEN_H
