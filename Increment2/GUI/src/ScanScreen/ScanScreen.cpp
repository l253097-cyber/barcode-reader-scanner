#include "ScanScreen/ScanScreen.h"

/*
 * ============================================================
 *  ScanScreen
 *  Scan screen: camera preview, capture button, scan result.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 2 : setupScanScreen(), startCameraPreview(), handleCaptureButton(), displayScanResult(), displayScanError() [EXTRA]
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

void ScanScreen::setupScanScreen()
{
    // ===== MEMBER 2 : START =====
    // TODO: Create QVideoWidget, capture button, result label; layout; connect captureButton->clicked to handleCaptureButton.
    // ===== MEMBER 2 : END =====
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
