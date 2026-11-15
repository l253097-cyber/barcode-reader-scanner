#include "MainWindow/POSMainWindow.h"
#include <QAction>
#include <QLabel>
#include <QToolBar>
#include <QVBoxLayout>
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
    //Create QStackedWidget, dashboard page with Scan/Order/Bill buttons, create the 4 screens (pass controller), add all to the stack, connect buttons to the handle... slots.
    setWindowTitle("Store POS");
    resize(1000, 650);

    // A stacked widget holds all screens but shows only one at a time
    screens = new QStackedWidget(this);
    setCentralWidget(screens);

    // ----- Dashboard page: a title and three buttons -----
    dashboardPage = new QWidget;
    QLabel* title = new QLabel("Store Point of Sale");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold;");

    scanButton = new QPushButton("Scan Product");
    orderButton = new QPushButton("Record Order");
    billButton = new QPushButton("Generate Bill");
    scanButton->setMinimumHeight(60);
    orderButton->setMinimumHeight(60);
    billButton->setMinimumHeight(60);

    QVBoxLayout* layout = new QVBoxLayout(dashboardPage);
    layout->setContentsMargins(120, 60, 120, 60);
    layout->setSpacing(20);
    layout->addWidget(title);
    layout->addStretch();
    layout->addWidget(scanButton);
    layout->addWidget(orderButton);
    layout->addWidget(billButton);
    layout->addStretch();

    // ----- The four screens, each gets the controller -----
    scanScreen = new ScanScreen(controller);
    orderScreen = new OrderScreen(controller);
    descriptionScreen = new ProductDescriptionScreen(controller);
    billScreen = new BillScreen(controller);

    // The order here must match the ScreenIndex enum in the header
    screens->addWidget(dashboardPage);     // DASHBOARD = 0
    screens->addWidget(scanScreen);        // SCAN = 1
    screens->addWidget(orderScreen);       // ORDER = 2
    screens->addWidget(descriptionScreen); // DESCRIPTION = 3
    screens->addWidget(billScreen);        // BILL = 4

    // ----- Buttons -> navigation slots -----
    connect(scanButton, &QPushButton::clicked, this, &POSMainWindow::handleScanNavigation);
    connect(orderButton, &QPushButton::clicked, this, &POSMainWindow::handleOrderNavigation);
    connect(billButton, &QPushButton::clicked, this, &POSMainWindow::handleBillNavigation);

    // A small toolbar so the cashier can always get back to another screen
    QToolBar* navBar = addToolBar("Navigation");
    navBar->setMovable(false);
    connect(navBar->addAction("Dashboard"), &QAction::triggered, this, &POSMainWindow::showDashboard);
    connect(navBar->addAction("Scan"), &QAction::triggered, this, &POSMainWindow::handleScanNavigation);
    connect(navBar->addAction("Order"), &QAction::triggered, this, &POSMainWindow::handleOrderNavigation);
    connect(navBar->addAction("Bill"), &QAction::triggered, this, &POSMainWindow::handleBillNavigation);

    showDashboard();
    // ===== MEMBER 1 : END =====
}

void POSMainWindow::showDashboard()
{
    // ===== MEMBER 1 : START =====
    //Show the dashboard page (index DASHBOARD).
    navigateToScreen(DASHBOARD);
    // ===== MEMBER 1 : END =====
}

void POSMainWindow::navigateToScreen(int screenIndex)
{
    // ===== MEMBER 1 : START =====
    //screens->setCurrentIndex(screenIndex) after checking the range.
        // Ignore an index that has no screen behind it
    if (screens == nullptr || screenIndex < 0 || screenIndex >= screens->count())
        return;

    screens->setCurrentIndex(screenIndex);
    // ===== MEMBER 1 : END =====
}

void POSMainWindow::handleScanNavigation()
{
    // ===== MEMBER 1 : START =====
    //navigateToScreen(SCAN) and call scanScreen->startCameraPreview().
    navigateToScreen(SCAN);

    // The camera preview only runs while the Scan screen is shown
    if (scanScreen != nullptr)
        scanScreen->startCameraPreview();
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
