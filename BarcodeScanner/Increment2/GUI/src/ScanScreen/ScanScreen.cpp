#include "ScanScreen/ScanScreen.h"
#include <QVBoxLayout>
#include <QMediaCaptureSession>
#include <QTimer>
#include "Camera/CameraHandler.h"

namespace {
QTimer* autoScanTimer = nullptr;
bool isScanningBusy = false;
}

void ScanScreen::setupScanScreen()
{
    cameraPreview = new QVideoWidget(this);
    cameraPreview->setMinimumSize(480, 360);

    captureButton = new QPushButton("Scan Now (Auto-Scan Active)", this);
    captureButton->setMinimumHeight(45);

    scanResultLabel = new QLabel("Auto-scanning... Hold a 6-digit product barcode in front of the camera.", this);
    scanResultLabel->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(cameraPreview);
    layout->addWidget(captureButton);
    layout->addWidget(scanResultLabel);

    autoScanTimer = new QTimer(this);
    autoScanTimer->setInterval(500);
    connect(autoScanTimer, &QTimer::timeout, this, [this]() {
        if (!this->isVisible() || isScanningBusy) {
            if (!this->isVisible()) autoScanTimer->stop();
            return;
        }

        isScanningBusy = true;
        std::string barcode = "";
        std::string message = "";
        if (controller->handleBarcodeScan(barcode, message)) {
            autoScanTimer->stop();
            displayScanResult(QString::fromStdString(barcode), QString::fromStdString(message));
        }
        isScanningBusy = false;
    });

    connect(captureButton, &QPushButton::clicked, this, [this]() {
        if (autoScanTimer && !autoScanTimer->isActive()) {
            scanResultLabel->setStyleSheet("color: black;");
            scanResultLabel->setText("Auto-scanning... Hold a 6-digit product barcode in front of the camera.");
            autoScanTimer->start();
        }
        handleCaptureButton();
    });
}

void ScanScreen::startCameraPreview()
{
    CameraHandler* camera = controller->getCameraHandler();
    if (camera == nullptr)
    {
        displayScanError("Camera handler not available");
        return;
    }

    if (camera->initializeCamera() == false)
    {
        displayScanError("No camera found");
        return;
    }

    // Standard, crash-free video preview output
    camera->getCaptureSession()->setVideoOutput(cameraPreview);

    scanResultLabel->setStyleSheet("color: black;");
    scanResultLabel->setText("Auto-scanning... Hold a 6-digit product barcode in front of the camera.");

    if (autoScanTimer != nullptr) {
        autoScanTimer->start();
    }
}

void ScanScreen::handleCaptureButton()
{
    if (isScanningBusy) return;
    isScanningBusy = true;

    std::string barcode = "";
    std::string message = "";

    bool ok = controller->handleBarcodeScan(barcode, message);
    isScanningBusy = false;

    if (ok)
    {
        if (autoScanTimer != nullptr) autoScanTimer->stop();
        displayScanResult(QString::fromStdString(barcode), QString::fromStdString(message));
    }
    else
    {
        displayScanError(QString::fromStdString(message));
    }
}

void ScanScreen::displayScanResult(const QString& barcode, const QString& message)
{
    scanResultLabel->setStyleSheet("color: green; font-weight: bold; font-size: 14px;");
    scanResultLabel->setText("Captured Barcode: " + barcode + "\n" + message + "\n(Click 'Scan Now' to scan another item)");
}

void ScanScreen::displayScanError(const QString& errorMessage)
{
    scanResultLabel->setStyleSheet("color: red; font-weight: bold;");
    scanResultLabel->setText("Error: " + errorMessage);
}