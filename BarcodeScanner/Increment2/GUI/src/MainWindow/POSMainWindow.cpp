#include "MainWindow/POSMainWindow.h"
#include <QAction>
#include <QLabel>
#include <QToolBar>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>

void POSMainWindow::setupMainWindow()
{
    setWindowTitle("Store POS");
    resize(1000, 650);

    screens = new QStackedWidget(this);
    setCentralWidget(screens);

    dashboardPage = new QWidget;
    QLabel* title = new QLabel("Store Point of Sale");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold;");

    scanButton = new QPushButton("Scan Product");
    orderButton = new QPushButton("Record Order");
    billButton = new QPushButton("Generate Bill");
    QPushButton* genBarcodeBtn = new QPushButton("Generate Barcode");

    scanButton->setMinimumHeight(60);
    orderButton->setMinimumHeight(60);
    billButton->setMinimumHeight(60);
    genBarcodeBtn->setMinimumHeight(60);

    QVBoxLayout* layout = new QVBoxLayout(dashboardPage);
    layout->setContentsMargins(120, 60, 120, 60);
    layout->setSpacing(20);
    layout->addWidget(title);
    layout->addStretch();
    layout->addWidget(scanButton);
    layout->addWidget(orderButton);
    layout->addWidget(billButton);
    layout->addWidget(genBarcodeBtn);
    layout->addStretch();

    scanScreen = new ScanScreen(controller);
    orderScreen = new OrderScreen(controller);
    descriptionScreen = new ProductDescriptionScreen(controller);
    billScreen = new BillScreen(controller);

    screens->addWidget(dashboardPage);     // DASHBOARD = 0
    screens->addWidget(scanScreen);        // SCAN = 1
    screens->addWidget(orderScreen);       // ORDER = 2
    screens->addWidget(descriptionScreen); // DESCRIPTION = 3
    screens->addWidget(billScreen);        // BILL = 4

    // Lambda popup for Generate Barcode (no extra .h/.cpp files needed!)
    auto openBarcodeGenerator = [this]() {
        bool ok = false;
        QString code = QInputDialog::getText(this, "Generate Barcode",
                                             "Enter 6-digit product code (non-zero start):",
                                             QLineEdit::Normal, "", &ok);
        if (!ok || code.trimmed().isEmpty()) return;

        std::string outPath, outMsg;
        if (controller->handleBarcodeGeneration(code.trimmed().toStdString(), outPath, outMsg)) {
            QMessageBox box(this);
            box.setWindowTitle("Barcode Generated");
            box.setText(QString::fromStdString(outMsg));
            QPixmap pix(QString::fromStdString(outPath));
            if (!pix.isNull())
                box.setIconPixmap(pix.scaled(360, 130, Qt::KeepAspectRatio));
            box.exec();
        } else {
            QMessageBox::warning(this, "Validation Error", QString::fromStdString(outMsg));
        }
    };

    connect(scanButton, &QPushButton::clicked, this, &POSMainWindow::handleScanNavigation);
    connect(orderButton, &QPushButton::clicked, this, &POSMainWindow::handleOrderNavigation);
    connect(billButton, &QPushButton::clicked, this, &POSMainWindow::handleBillNavigation);
    connect(genBarcodeBtn, &QPushButton::clicked, this, openBarcodeGenerator);

    QToolBar* navBar = addToolBar("Navigation");
    navBar->setMovable(false);
    connect(navBar->addAction("Dashboard"), &QAction::triggered, this, &POSMainWindow::showDashboard);
    connect(navBar->addAction("Scan"), &QAction::triggered, this, &POSMainWindow::handleScanNavigation);
    connect(navBar->addAction("Order"), &QAction::triggered, this, &POSMainWindow::handleOrderNavigation);
    connect(navBar->addAction("Bill"), &QAction::triggered, this, &POSMainWindow::handleBillNavigation);
    connect(navBar->addAction("Generate Barcode"), &QAction::triggered, this, openBarcodeGenerator);

    showDashboard();
}

void POSMainWindow::showDashboard()
{
    navigateToScreen(DASHBOARD);
}

void POSMainWindow::navigateToScreen(int screenIndex)
{
    if (screens == nullptr || screenIndex < 0 || screenIndex >= screens->count())
        return;

    screens->setCurrentIndex(screenIndex);
}

void POSMainWindow::handleScanNavigation()
{
    navigateToScreen(SCAN);

    if (scanScreen != nullptr)
        scanScreen->startCameraPreview();
}

void POSMainWindow::handleOrderNavigation()
{
    navigateToScreen(ORDER);
}

void POSMainWindow::handleBillNavigation()
{
    navigateToScreen(BILL);
}