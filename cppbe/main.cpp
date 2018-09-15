#include <iostream>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/logger.h>
#include <chrono>

#define ever (;;)

int main() {
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *dev = 0;
    libfreenect2::PacketPipeline *pipeline = 0;

    if(freenect2.enumerateDevices() == 0) {
        std::cout << "no device connected!" << std::endl;
        return -1;
    }

    pipeline = new libfreenect2::CpuPacketPipeline();
    std::string serial = freenect2.getDefaultDeviceSerialNumber();

    dev = freenect2.openDevice(serial, pipeline);

    unsigned int types = libfreenect2::Frame::Color;

    libfreenect2::SyncMultiFrameListener listener(types);
    libfreenect2::FrameMap frames;
    dev->setColorFrameListener(&listener);
    dev->setIrAndDepthFrameListener(&listener);

    dev->startStreams(true, false);


    std::cout << "device serial: " << dev->getSerialNumber() << std::endl;
    std::cout << "device firmware: " << dev->getFirmwareVersion() << std::endl;

    auto time = std::chrono::high_resolution_clock().now();

    for ever {
        listener.waitForNewFrame(frames);
        libfreenect2::Frame *rgb   = frames[libfreenect2::Frame::Color];

        auto oldtime = time;
        time = std::chrono::high_resolution_clock().now();
        auto td = time - oldtime;

        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(td).count() << std::endl;
    }
}
