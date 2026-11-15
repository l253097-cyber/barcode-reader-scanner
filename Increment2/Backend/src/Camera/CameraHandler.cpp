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
bool CameraHandler::captureFrame()
{
    qDebug() << "Capture requested";

    if (imageCapture == nullptr || !imageCapture->isReadyForCapture())
    {    // ===== MEMBER 4 : START =====
        qDebug() << "Camera is not ready";
        return false;
        // ===== MEMBER 4 : END =====
    }

    capturedImage = QImage();

    QObject::connect(imageCapture, &QImageCapture::imageAvailable,
        imageCapture,
        [this](int id, const QVideoFrame& frame)
        {
            capturedImage = frame.toImage();

            qDebug() << "Image received!";
            qDebug() << "Image ID:" << id;
            qDebug() << "Image size:" << capturedImage.size();
            qDebug() << "Image null:" << capturedImage.isNull();
        },
        Qt::SingleShotConnection);

    imageCapture->capture();

    qDebug() << "Capture request sent";
    return true;
}

QImage CameraHandler::convertFrameToImageData() const
{
    // ===== MEMBER 4 : START =====
    if (capturedImage.isNull())
        //if pic hasn't arrived yet, or if it was too flat to be useful, return an empty QImage
        return QImage();

    // 1) Gray picture
    //  every pixel =1 byte (0 = dark, 255 = light)
    QImage gray = capturedImage.convertToFormat(QImage::Format_Grayscale8);

    // 2) Threshold: find darkest and brightest pixel in the middle row, and set threshold to their average
    const uchar* middleRow = gray.constScanLine(gray.height() / 2);
    int darkest = 255, brightest = 0;
    for (int x = 0; x < gray.width(); x++)
    {
        if (middleRow[x] < darkest)   darkest = middleRow[x];
        if (middleRow[x] > brightest) brightest = middleRow[x];
    }
    //flar bars can't be scanned, so if the picture is too flat, return an empty QImage
    if (brightest - darkest < 50)
        return QImage();
    int threshold = (darkest + brightest) / 2;

    // 3) every pixel darker than threshold, set to black; else set to white
    for (int y = 0; y < gray.height(); y++)
    {
        uchar* line = gray.scanLine(y);
        for (int x = 0; x < gray.width(); x++)
            line[x] = (line[x] < threshold) ? 0 : 255;
    }
    return gray;
    // ===== MEMBER 4 : END =====
}
