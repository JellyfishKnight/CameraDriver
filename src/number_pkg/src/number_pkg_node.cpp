//
// Created by wjy on 22-7-12.
//
//
// Created by 17703 on 2022/5/14.
//
#include "ros/ros.h"
#include "number_pkg/Number.h"
#include <string>

using namespace std;
using namespace cv;
using namespace ml;


int main() {
    string readRoot = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/SVM_img/";
    string saveRoot = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/SVM.xml";
    Number number(readRoot, saveRoot);
    number.start();
    return 0;
}