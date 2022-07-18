//
// Created by wjy on 22-7-10.
//
#include "recognize_pkg/System.h"
#include "ros/ros.h"
#include "receive_pkg/ImgReceiver.h"
#include "receive_pkg/Int32Receiver.h"

using namespace ros;


int main(int argc, char* argv[]) {
    init(argc, argv, "recognize_pkg");
    int choice;
    cout << "Input 1 to start camera, 2 to start video" << endl;
    cin >> choice;
    if (choice == 1) {   //相机调试
        System system;
        ImgReceiver mvReceiver("Driver_Node");
        mvReceiver.subscribe(System::Start);
        while (ok()) {
            spinOnce();
        }
    } else {   //视频调试
        Int32Receiver int32Receiver("NumberBack");
        System system("/home/wjy/Projects/RMlearning/CameraDriverWS/src/TestVideo/sample_red.avi", RED);
    }
    return 0;
}