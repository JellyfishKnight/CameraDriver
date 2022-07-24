//
// Created by wjy on 22-7-10.
//
#include "recognize_pkg/System.h"
#include "ros/ros.h"
#include "receive_pkg/ImgReceiver.h"

using namespace ros;


int main(int argc, char* argv[]) {
    init(argc, argv, "recognize_pkg");
    System system;
    ImgReceiver mvReceiver("Driver_Node");
    mvReceiver.subscribe(System::Start);
    while (ok()) {
        spinOnce();
    }
    return 0;
}