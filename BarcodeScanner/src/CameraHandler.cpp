#include "Camera/CameraHandler.h"
#include <QCameraDevice>
#include <QMediaDevices>
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

bool CameraHandler::initializeCamera()
{
    // ===== MEMBER 1 : START =====
    //Create QCamera, QMediaCaptureSession, QImageCapture; link them; camera->start(). Set cameraAvailable.
        // Calling it twice must not open a second camera
    if (camera != nullptr)
        return true;

    // Ask Windows for the default camera (the laptop webcam)
    const QCameraDevice device = QMediaDevices::defaultVideoInput();
    if (device.isNull())
    {
        cameraAvailable = false;
        return false;
    }

    // The session connects the camera to the preview and to image capture
    camera = new QCamera(device);
    captureSession = new QMediaCaptureSession;
    imageCapture = new QImageCapture;

    captureSession->setCamera(camera);
    captureSession->setImageCapture(imageCapture);
    camera->start();

    cameraAvailable = true;
    return true;
    // ===== MEMBER 1 : END =====
}

bool CameraHandler::checkCameraStatus() const
{
    // ===== MEMBER 1 : START =====
    //Return true if camera exists and is active.
        // The camera starts in the background, so this can be false for a moment
    // right after initializeCamera().
    return camera != nullptr && camera->isActive() && camera->error() == QCamera::NoError;
    // ===== MEMBER 1 : END =====
}

void CameraHandler::releaseCamera()
{
    // ===== MEMBER 1 : START =====
    //Stop camera, delete the 3 Qt objects, set pointers to nullptr (safe to call twice).
    if (camera != nullptr)
        camera->stop();

    // Unlink the pieces first, then delete them, so nothing points at a deleted object
    if (captureSession != nullptr)
    {
        captureSession->setCamera(nullptr);
        captureSession->setImageCapture(nullptr);
    }

    delete imageCapture;    imageCapture = nullptr;
    delete captureSession;  captureSession = nullptr;
    delete camera;          camera = nullptr;
    cameraAvailable = false;   // safe to call twice: deleting nullptr does nothing
    // ===== MEMBER 1 : END =====
}

bool CameraHandler::captureFrame()
{
    // ===== MEMBER 4 : START =====
    // TODO: Call imageCapture->capture(). Qt capture is asynchronous: connect imageCaptured signal and store the image in capturedImage.
    return false;
    // ===== MEMBER 4 : END =====
}

QImage CameraHandler::convertFrameToImageData() const
{
    // ===== MEMBER 4 : START =====
    // TODO: Return capturedImage in the format the Increment 1 BarcodeScanner/Decoder expects (e.g. convertToFormat(Grayscale8)).
    return QImage();
    // ===== MEMBER 4 : END =====
}
