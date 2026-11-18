#include "MainWindow/POSMainWindow.h"
#include <QAction>
#include <QFileDialog>
#include <QFrame>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QStandardPaths>
#include <QToolBar>
#include <QVBoxLayout>

void POSMainWindow::setupMainWindow()
{
    setWindowTitle("Store POS");
    resize(1050, 720);

    // Outer background container that centers the main white card in the middle of the screen
    QWidget* centralContainer = new QWidget(this);
    QVBoxLayout* outerLayout = new QVBoxLayout(centralContainer);
    outerLayout->setContentsMargins(40, 30, 40, 30);
    outerLayout->setAlignment(Qt::AlignCenter);

    // Centered white card wrapper for all screens
    QFrame* mainCard = new QFrame(centralContainer);
    mainCard->setObjectName("CardContainer");
    mainCard->setMinimumSize(720, 560);
    mainCard->setMaximumWidth(880);

    QVBoxLayout* cardLayout = new QVBoxLayout(mainCard);
    cardLayout->setContentsMargins(32, 28, 32, 28);

    screens = new QStackedWidget(mainCard);
    screens->setStyleSheet("QStackedWidget { background-color: #FFFFFF; border: none; }");
    screens->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cardLayout->addWidget(screens);

    outerLayout->addWidget(mainCard, 0, Qt::AlignCenter);
    setCentralWidget(centralContainer);

    // ================= DASHBOARD PAGE =================
    dashboardPage = new QWidget;
    dashboardPage->setObjectName("DashboardPage");
    dashboardPage->setStyleSheet("#DashboardPage { background-color: #FFFFFF; }");

    QLabel* title = new QLabel("Store Point of Sale");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 30px; font-weight: bold; color: #4A1FD1; background: transparent;");

    QLabel* subtitle = new QLabel("Fast Barcode Scanning, Order Management & Billing");
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("font-size: 14px; color: #6E6299; background: transparent; margin-bottom: 10px;");

    scanButton = new QPushButton("Scan Product");
    orderButton = new QPushButton("Record Order");
    billButton = new QPushButton("Generate Bill");
    QPushButton* genBarcodeBtn = new QPushButton("Generate Barcode");

    QString primaryBtnStyle =
        "QPushButton { background-color: #5E2CED; color: #FFFFFF; border: none; border-radius: 10px; font-weight: bold; font-size: 15px; }"
        "QPushButton:hover { background-color: #7245F5; }"
        "QPushButton:pressed { background-color: #461AB8; }";

    scanButton->setStyleSheet(primaryBtnStyle);
    orderButton->setStyleSheet(primaryBtnStyle);
    billButton->setStyleSheet(primaryBtnStyle);

    genBarcodeBtn->setStyleSheet(
        "QPushButton { background-color: #EDE6FE; color: #5E2CED; border: 1.5px solid #C8B5FA; border-radius: 10px; font-weight: bold; font-size: 15px; }"
        "QPushButton:hover { background-color: #E0D4FD; }"
        "QPushButton:pressed { background-color: #D0BEFC; }"
        );

    const int btnWidth = 360;
    const int btnHeight = 56;
    for (QPushButton* btn : { scanButton, orderButton, billButton, genBarcodeBtn }) {
        btn->setMinimumSize(btnWidth, btnHeight);
        btn->setMaximumWidth(btnWidth);
    }

    QVBoxLayout* layout = new QVBoxLayout(dashboardPage);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(16);
    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addSpacing(10);
    layout->addWidget(scanButton, 0, Qt::AlignHCenter);
    layout->addWidget(orderButton, 0, Qt::AlignHCenter);
    layout->addWidget(billButton, 0, Qt::AlignHCenter);
    layout->addWidget(genBarcodeBtn, 0, Qt::AlignHCenter);
    layout->addStretch();

    // ================= FEATURE SCREENS =================
    scanScreen = new ScanScreen(controller);
    orderScreen = new OrderScreen(controller);
    descriptionScreen = new ProductDescriptionScreen(controller);
    billScreen = new BillScreen(controller);

    scanScreen->setObjectName("ScanPage");
    orderScreen->setObjectName("OrderPage");
    descriptionScreen->setObjectName("DescPage");
    billScreen->setObjectName("BillPage");

    scanScreen->setStyleSheet("#ScanPage { background-color: #FFFFFF; }");
    orderScreen->setStyleSheet("#OrderPage { background-color: #FFFFFF; }");
    descriptionScreen->setStyleSheet("#DescPage { background-color: #FFFFFF; }");
    billScreen->setStyleSheet("#BillPage { background-color: #FFFFFF; }");

    screens->addWidget(dashboardPage);     // DASHBOARD = 0
    screens->addWidget(scanScreen);        // SCAN = 1
    screens->addWidget(orderScreen);       // ORDER = 2
    screens->addWidget(descriptionScreen); // DESCRIPTION = 3
    screens->addWidget(billScreen);        // BILL = 4

    // ================= BARCODE GENERATOR POPUP (ASK USER WHERE TO SAVE) =================
    auto openBarcodeGenerator = [this]() {
        bool ok = false;
        QString code = QInputDialog::getText(this, "Generate Barcode",
                                             "Enter 6-digit product code (non-zero start):",
                                             QLineEdit::Normal, "", &ok);
        if (!ok || code.trimmed().isEmpty()) return;

        QString cleanCode = code.trimmed();
        QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString defaultPath = defaultDir + "/" + cleanCode + ".bmp";

        QString savePath = QFileDialog::getSaveFileName(
            this,
            "Save Barcode Image",
            defaultPath,
            "Bitmap Image (*.bmp)"
            );
        if (savePath.isEmpty()) return;

        if (!savePath.endsWith(".bmp", Qt::CaseInsensitive))
            savePath += ".bmp";

        std::string outPath = savePath.toStdString();
        std::string outMsg;
        if (controller->handleBarcodeGeneration(cleanCode.toStdString(), outPath, outMsg)) {
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

    // ================= TOP NAVIGATION TOOLBAR =================
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
    screens->currentWidget()->show();
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
    if (controller != nullptr && billScreen != nullptr) {
        Bill bill = controller->handleBillGeneration();
        if (!bill.getBillId().empty()) {
            billScreen->displayBillDetails(bill);
        }
    }
    navigateToScreen(BILL);
}