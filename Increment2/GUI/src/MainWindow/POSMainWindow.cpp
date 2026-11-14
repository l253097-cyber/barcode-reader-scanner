#include "MainWindow/POSMainWindow.h"

/*
 * ============================================================
 *  POSMainWindow
 *  Main window: dashboard + QStackedWidget navigation.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 1 : setupMainWindow(), showDashboard(), navigateToScreen(), handleScanNavigation(), handleOrderNavigation() [EXTRA], handleBillNavigation() [EXTRA]
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

void POSMainWindow::setupMainWindow()
{
    // ===== MEMBER 1 : START =====
    // TODO: Create QStackedWidget, dashboard page with Scan/Order/Bill buttons, create the 4 screens (pass controller), add all to the stack, connect buttons to the handle... slots.
    // ===== MEMBER 1 : END =====
}

void POSMainWindow::showDashboard()
{
    // ===== MEMBER 1 : START =====
    // TODO: Show the dashboard page (index DASHBOARD).
    // ===== MEMBER 1 : END =====
}

void POSMainWindow::navigateToScreen(int screenIndex)
{
    // ===== MEMBER 1 : START =====
    // TODO: screens->setCurrentIndex(screenIndex) after checking the range.
    // ===== MEMBER 1 : END =====
}

void POSMainWindow::handleScanNavigation()
{
    // ===== MEMBER 1 : START =====
    // TODO: navigateToScreen(SCAN) and call scanScreen->startCameraPreview().
    // ===== MEMBER 1 : END =====
}

void POSMainWindow::handleOrderNavigation()
{
    // ===== MEMBER 1 (EXTRA - not in the official final list) : START =====
    // TODO: navigateToScreen(ORDER).
    // ===== MEMBER 1 (EXTRA - not in the official final list) : END =====
}

void POSMainWindow::handleBillNavigation()
{
    // ===== MEMBER 1 (EXTRA - not in the official final list) : START =====
    // TODO: navigateToScreen(BILL).
    // ===== MEMBER 1 (EXTRA - not in the official final list) : END =====
}
