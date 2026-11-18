#include "ScanScreen/ScanScreen.h"
#include <QVBoxLayout>
#include <QMediaCaptureSession>
#include "Camera/CameraHandler.h"

void ScanScreen::setupScanScreen()
{
    cameraPreview = new QVideoWidget(this);
    cameraPreview->setMinimumSize(480, 360);
    captureButton = new QPushButton("Capture", this);
    scanResultLabel = new QLabel("Scan result will appear here", this);
    scanResultLabel->setWordWrap(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(cameraPreview);
    layout->addWidget(captureButton);
    layout->addWidget(scanResultLabel);
    connect(captureButton, &QPushButton::clicked, this, &ScanScreen::handleCaptureButton);
}

void ScanScreen::startCameraPreview()
{
    // ===== MEMBER 2 =====
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
    camera->getCaptureSession()->setVideoOutput(cameraPreview);
}

void ScanScreen::handleCaptureButton()
{
    // ===== MEMBER 2  =====
    std::string barcode = "";
    std::string message = "";

    bool ok = controller->handleBarcodeScan(barcode, message);
    if (ok)
    {
        displayScanResult(QString::fromStdString(barcode), QString::fromStdString(message));
    }
    else
    {
        displayScanError(QString::fromStdString(message));
    }
}

void ScanScreen::displayScanResult(const QString& barcode, const QString& message)
{
    // ===== MEMBER 2  =====
    scanResultLabel->setStyleSheet("color: green;");
    scanResultLabel->setText("Barcode: " + barcode + "\n" + message);

}

void ScanScreen::displayScanError(const QString& errorMessage)
{
    // ===== MEMBER 2 =====
    scanResultLabel->setStyleSheet("color: red;");
    scanResultLabel->setText("Error: " + errorMessage);
}