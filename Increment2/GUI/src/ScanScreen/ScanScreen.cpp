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
    // ===== MEMBER 2 : START =====
    // TODO: controller->getCameraHandler()->initializeCamera() then captureSession->setVideoOutput(cameraPreview).
    // ===== MEMBER 2 : END =====
}

void ScanScreen::handleCaptureButton()
{
    // ===== MEMBER 2 : START =====
    // TODO: Call controller->handleBarcodeScan(barcode, msg); show with displayScanResult() or displayScanError().
    // ===== MEMBER 2 : END =====
}

void ScanScreen::displayScanResult(const QString& barcode, const QString& message)
{
    // ===== MEMBER 2 : START =====
    // TODO: Show barcode + product info in scanResultLabel.
    // ===== MEMBER 2 : END =====
}

void ScanScreen::displayScanError(const QString& errorMessage)
{
    // ===== MEMBER 2 (EXTRA - not in the official final list) : START =====
    // TODO: Show errorMessage (e.g. in red) in scanResultLabel.
    // ===== MEMBER 2 (EXTRA - not in the official final list) : END =====
}
