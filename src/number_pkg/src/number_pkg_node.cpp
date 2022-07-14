//
// Created by wjy on 22-7-12.
//
//
// Created by 17703 on 2022/5/14.
//
#include "ros/ros.h"
#include "number_pkg/Number.h"
#include "receive_pkg/ImgReceiver.h"
#include <string>

using namespace std;
using namespace cv;
using namespace ml;
using namespace ros;


int main(int argc, char* argv[]) {
    init(argc, argv, "number_pkg");
    string dataRoot = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/SVM.xml";
    string imgRoot = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/SVM_img/";
    ImgReceiver imgReceiver("Number");
    Number number(dataRoot, dataRoot);
    imgReceiver.subscribe(Number::start);
//    Number number(imgRoot, dataRoot);
//    Number::start();
    return 0;
}