#include "BillScreen/BillScreen.h"

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
    // ===== MEMBER 5 : END =====
}

void BillScreen::displayBillDetails(const Bill& bill)
{
    // ===== MEMBER 5 : START =====
    // TODO: Fill table and subtotal/tax/discount/payable labels from the bill.
    // ===== MEMBER 5 : END =====
}

void BillScreen::handlePaymentInput()
{
    // ===== MEMBER 5 : START =====
    // TODO: Validate amount + merchant fields while the user types; enable/disable Confirm button.
    // ===== MEMBER 5 : END =====
}

void BillScreen::handleConfirmPayment()
{
    // ===== MEMBER 5 : START =====
    // TODO: Call controller->handlePayment(amount, mode, merchant); on success call displayPaymentStatus("Paid").
    // ===== MEMBER 5 : END =====
}

void BillScreen::displayPaymentStatus(const QString& status)
{
    // ===== MEMBER 5 (EXTRA - not in the official final list) : START =====
    // TODO: Show status (Paid / Unpaid / error) in paymentStatusLabel.
    // ===== MEMBER 5 (EXTRA - not in the official final list) : END =====
}

void BillScreen::handlePrintOrCloseBill()
{
    // ===== MEMBER 5 (EXTRA - not in the official final list) : START =====
    // TODO: Print or close the bill and go back to the dashboard.
    // ===== MEMBER 5 (EXTRA - not in the official final list) : END =====
}
