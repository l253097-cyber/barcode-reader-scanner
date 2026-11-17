#include "Camera/CameraHandler.h"
#include <QCameraDevice>
#include <QVideoFrame>
#include <QMediaDevices>
#include <QDebug> 
#include<iostream>

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
// Asks the camera for one picture (the picture arrives later, see below)
bool CameraHandler::captureFrame()
{
    // ===== MEMBER 4 : START =====
    // Defensive programming: if the camera is not ready, do not try to capture
    if (imageCapture == nullptr || !imageCapture->isReadyForCapture())
        return false;

    // Clear the old image so an old picture is never mistaken for a new one
    capturedImage = QImage();

    // The picture does not arrive immediately: capture is asynchronous, so the camera
    // sends a signal when the picture is ready. SingleShotConnection makes this run only once.
    QObject::connect(imageCapture, &QImageCapture::imageAvailable,
        imageCapture,
        [this](int, const QVideoFrame& frame)
        {
            capturedImage = frame.toImage();
        },
        Qt::SingleShotConnection);

    imageCapture->capture();
    return true;       // request sent; the picture is not ready yet
    // ===== MEMBER 4 : END =====
}

// Converts the coloured picture into a black and white one for the scanner
QImage CameraHandler::convertFrameToImageData() const
{
    // ===== MEMBER 4 : START =====
    // If the picture has not arrived yet, return an empty QImage
    if (capturedImage.isNull())
        return QImage();

    // 1) Gray picture: bars do not depend on colour.
    //    Every pixel is 1 byte (0 = dark, 255 = light)
    QImage gray = capturedImage.convertToFormat(QImage::Format_Grayscale8);

    // 2) Threshold: find the darkest and brightest pixel in the middle row
    //    and take their average as the cut-off value
    const uchar* middleRow = gray.constScanLine(gray.height() / 2);
    int darkest = 255, brightest = 0;
    for (int x = 0; x < gray.width(); x++)
    {
        if (middleRow[x] < darkest)   darkest = middleRow[x];
        if (middleRow[x] > brightest) brightest = middleRow[x];
    }
    // A flat picture has no visible bars, so it cannot be scanned: return an empty QImage
    if (brightest - darkest < 50)
        return QImage();
    int threshold = (darkest + brightest) / 2;

    // 3) Every pixel darker than the threshold becomes black, the rest becomes white
    for (int y = 0; y < gray.height(); y++)
    {
        uchar* line = gray.scanLine(y);
        for (int x = 0; x < gray.width(); x++)
            line[x] = (line[x] < threshold) ? 0 : 255;
    }
    return gray;
    // ===== MEMBER 4 : END =====
}
