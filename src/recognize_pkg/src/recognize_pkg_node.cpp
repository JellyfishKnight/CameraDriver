//
// Created by wjy on 22-7-10.
//
#include "recognize_pkg/System.h"
#include "ros/ros.h"
#include "receive_pkg/MVReceiver.h"

using namespace ros;

int main(int argc, char* argv[]) {
    init(argc, argv, "recognize_pkg");
    MVReceiver mvReceiver;
    System system;
    mvReceiver.subscribe(System::Receive);
    system.Start();
    while(ok()) {
        spinOnce();
    }
    return 0;
}