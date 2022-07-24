//
// Created by wjy on 7/24/22.
//
#include "recognize_pkg/System.h"
#include "ros/ros.h"

using namespace ros;


int main(int argc, char* argv[]) {
    init(argc, argv, "recognize_pkg");
    System system("/home/wjy/Projects/RMlearning/CameraDriverWS/src/TestVideo/sample_red.avi", RED);
    System::Start();
    return 0;
}