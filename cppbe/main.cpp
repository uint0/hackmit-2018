#include <iostream>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/logger.h>
#include <chrono>
#include <thread>

#include "algo.h"


#define ever (;;)

static void run(algo *algo1) {
    //auto algo2 = new class algo(*algo1);
    algo1->run();
    //delete algo2;
}

int main() {
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *dev = 0;
    libfreenect2::PacketPipeline *pipeline = 0;

    if(freenect2.enumerateDevices() == 0) {
        std::cout << "no device connected!" << std::endl;
        return 0;
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
    auto start = time;
    int index = 0;

    auto alg = new algo();

    for ever {
        index++;

        listener.waitForNewFrame(frames);
        libfreenect2::Frame *rgb   = frames[libfreenect2::Frame::Color];

        alg->loadState((uint8_t *)rgb->data);

        listener.release(frames);

        if (index == 10) {
            start = std::chrono::high_resolution_clock().now();

        }
        if (index > 10) {
            auto oldtime = time;
            time = std::chrono::high_resolution_clock().now();
            auto td = time - oldtime;
            printf("TIM: [%lu] AVG: [%lu]\r", std::chrono::duration_cast<std::chrono::microseconds>(td).count(), std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock().now()-start).count()/(index - 10));
        }


        //alg->run();

        if (index % 512 == 511) {
            printf("Spawned thread\n");
            std::thread t1(run, alg);
            t1.detach();
        }
    }
}
