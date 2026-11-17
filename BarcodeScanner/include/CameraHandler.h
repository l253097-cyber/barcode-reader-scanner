#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <QCamera>
#include <QMediaCaptureSession>
#include <QImageCapture>
#include <QImage>

/*
 * ============================================================
 *  CameraHandler
 *  Qt6 camera control: start, capture frame, convert to image data for the Increment 1 scanner.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 1 : initializeCamera(), checkCameraStatus(), releaseCamera()
 *    Member 4 : captureFrame(), convertFrameToImageData()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class CameraHandler {
private:
    QCamera* camera = nullptr;
    QMediaCaptureSession* captureSession = nullptr;
    QImageCapture* imageCapture = nullptr;
    QImage capturedImage;
    bool cameraAvailable = false;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    CameraHandler() = default;
    ~CameraHandler() { releaseCamera(); }
    CameraHandler(const CameraHandler&) = delete;
    CameraHandler& operator=(const CameraHandler&) = delete;
    QMediaCaptureSession* getCaptureSession() const { return captureSession; }  // GUI preview uses this
    const QImage& getCapturedImage() const { return capturedImage; }
    bool isCameraAvailable() const { return cameraAvailable; }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    bool initializeCamera();   // Member 1
    bool checkCameraStatus() const;   // Member 1
    void releaseCamera();   // Member 1
    bool captureFrame();   // Member 4
    QImage convertFrameToImageData() const;   // Member 4
};

#endif // CAMERAHANDLER_H
