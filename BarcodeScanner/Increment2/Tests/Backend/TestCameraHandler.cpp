// Camera lifecycle test. Passes with or without a camera attached.
#include <QGuiApplication>
#include <cassert>
#include <iostream>
#include "Camera/CameraHandler.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    CameraHandler handler;

    if (!handler.initializeCamera())
    {
        assert(!handler.isCameraAvailable());
        std::cout << "[TestCameraHandler] no camera found, lifecycle skipped\n";
        return 0;
    }

    assert(handler.isCameraAvailable());
    assert(handler.initializeCamera());        // second call opens no second camera

    handler.releaseCamera();
    assert(!handler.isCameraAvailable());
    assert(!handler.checkCameraStatus());
    handler.releaseCamera();                   // calling twice is safe

    std::cout << "[TestCameraHandler] all tests passed\n";
    return 0;
}