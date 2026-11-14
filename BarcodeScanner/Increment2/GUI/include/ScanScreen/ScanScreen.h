#ifndef SCANSCREEN_H
#define SCANSCREEN_H

#include <QVideoWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include "POSController/POSController.h"

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

class ScanScreen : public QWidget {
    Q_OBJECT
private:
    QVideoWidget* cameraPreview = nullptr;
    QPushButton* captureButton = nullptr;
    QLabel* scanResultLabel = nullptr;
    POSController* controller = nullptr;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    explicit ScanScreen(POSController* controller, QWidget* parent = nullptr)
        : QWidget(parent), controller(controller) { setupScanScreen(); }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    void setupScanScreen();   // Member 2
    void startCameraPreview();   // Member 2
    void displayScanResult(const QString& barcode, const QString& message);   // Member 2
    void displayScanError(const QString& errorMessage);   // Member 2 (EXTRA)

public slots:
    void handleCaptureButton();   // Member 2
};

#endif // SCANSCREEN_H
