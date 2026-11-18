#include "Camera/CameraHandler.h"
#include <QCameraDevice>
#include <QMediaDevices>
#include <QVideoSink>
#include <QVideoFrame>
#include <vector>
#include <algorithm>
#include <cmath>

namespace {

// Isolates a barcode shown on a bright phone screen (or white paper) from dark room background,
// and trims away background clutter using horizontal bar-transition density.
QImage isolatePhoneBarcode(const QImage& grayImg)
{
    if (grayImg.isNull() || grayImg.width() < 60 || grayImg.height() < 40)
        return grayImg;

    const int w = grayImg.width();
    const int h = grayImg.height();

    // 1. Find the bright phone screen / white paper region (top 25% brightest pixels)
    int maxPixel = 0;
    for (int y = 0; y < h; y += 2) {
        const uchar* line = grayImg.constScanLine(y);
        for (int x = 0; x < w; x += 2) {
            if (line[x] > maxPixel) maxPixel = line[x];
        }
    }

    int brightThresh = static_cast<int>(maxPixel * 0.72);
    int screenLeft = w, screenRight = 0, screenTop = h, screenBottom = 0;
    int brightCount = 0;

    for (int y = 0; y < h; ++y) {
        const uchar* line = grayImg.constScanLine(y);
        int rowBright = 0;
        for (int x = 0; x < w; ++x) {
            if (line[x] >= brightThresh) {
                ++rowBright;
                if (x < screenLeft) screenLeft = x;
                if (x > screenRight) screenRight = x;
            }
        }
        if (rowBright > w / 10) {
            ++brightCount;
            if (y < screenTop) screenTop = y;
            if (y > screenBottom) screenBottom = y;
        }
    }

    // Use the detected bright phone screen box if valid, otherwise center 70%
    int boxX = static_cast<int>(w * 0.15);
    int boxY = static_cast<int>(h * 0.15);
    int boxW = static_cast<int>(w * 0.70);
    int boxH = static_cast<int>(h * 0.70);

    if (brightCount > 15 && (screenRight - screenLeft) > 50 && (screenBottom - screenTop) > 25) {
        // Inset slightly by 3% so dark bezel edges of the phone are excluded
        int insetX = static_cast<int>((screenRight - screenLeft) * 0.03);
        int insetY = static_cast<int>((screenBottom - screenTop) * 0.05);
        boxX = std::max(0, screenLeft + insetX);
        boxY = std::max(0, screenTop + insetY);
        boxW = std::min(w - boxX, std::max(40, (screenRight - screenLeft) - 2 * insetX));
        boxH = std::min(h - boxY, std::max(20, (screenBottom - screenTop) - 2 * insetY));
    }

    QImage screenCrop = grayImg.copy(boxX, boxY, boxW, boxH);

    // 2. Refine vertically inside the phone screen to the rows where the black bars actually sit
    const int sw = screenCrop.width();
    const int sh = screenCrop.height();
    std::vector<int> rowTransitions(sh, 0);
    int maxRowScore = 0;

    for (int y = 0; y < sh; ++y) {
        const uchar* line = screenCrop.constScanLine(y);
        int transitions = 0;
        for (int x = 1; x < sw; ++x) {
            if (std::abs(static_cast<int>(line[x]) - static_cast<int>(line[x - 1])) > 28) {
                ++transitions;
            }
        }
        rowTransitions[y] = transitions;
        if (transitions > maxRowScore) maxRowScore = transitions;
    }

    if (maxRowScore >= 12) {
        int rowThresh = static_cast<int>(maxRowScore * 0.45);
        int topY = sh, bottomY = 0;
        for (int y = 0; y < sh; ++y) {
            if (rowTransitions[y] >= rowThresh) {
                if (y < topY) topY = y;
                if (y > bottomY) bottomY = y;
            }
        }
        if (bottomY - topY >= 10) {
            int padY = static_cast<int>((bottomY - topY) * 0.10);
            int finalY = std::max(0, topY - padY);
            int finalH = std::min(sh - finalY, (bottomY - topY) + 2 * padY);
            screenCrop = screenCrop.copy(0, finalY, sw, finalH);
        }
    }

    return screenCrop;
}

} // namespace

bool CameraHandler::initializeCamera()
{
    if (camera != nullptr)
        return true;

    const QCameraDevice device = QMediaDevices::defaultVideoInput();
    if (device.isNull())
    {
        cameraAvailable = false;
        return false;
    }

    camera = new QCamera(device);
    captureSession = new QMediaCaptureSession;
    imageCapture = new QImageCapture;

    captureSession->setCamera(camera);
    captureSession->setImageCapture(imageCapture);
    camera->start();

    cameraAvailable = true;
    return true;
}

bool CameraHandler::checkCameraStatus() const
{
    return camera != nullptr && camera->isActive() && camera->error() == QCamera::NoError;
}

void CameraHandler::releaseCamera()
{
    if (camera != nullptr)
        camera->stop();

    if (captureSession != nullptr)
    {
        captureSession->setCamera(nullptr);
        captureSession->setImageCapture(nullptr);
        captureSession->setVideoSink(nullptr);
    }

    delete imageCapture;    imageCapture = nullptr;
    delete captureSession;  captureSession = nullptr;
    delete camera;          camera = nullptr;
    cameraAvailable = false;
}

bool CameraHandler::captureFrame()
{
    if (captureSession == nullptr || !checkCameraStatus())
        return false;

    QVideoSink* sink = captureSession->videoSink();
    if (sink != nullptr)
    {
        QVideoFrame frame = sink->videoFrame();
        if (frame.isValid())
        {
            QImage img = frame.toImage();
            if (!img.isNull())
            {
                capturedImage = img;
                return true;
            }
        }
    }

    return !capturedImage.isNull();
}

QImage CameraHandler::convertFrameToImageData() const
{
    if (capturedImage.isNull())
        return QImage();

    QImage gray = capturedImage.convertToFormat(QImage::Format_Grayscale8);
    return isolatePhoneBarcode(gray);
}