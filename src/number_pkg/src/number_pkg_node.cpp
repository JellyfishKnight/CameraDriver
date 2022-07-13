//
// Created by wjy on 22-7-12.
//
//
// Created by 17703 on 2022/5/14.
//
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/ml.hpp"
#include "number_pkg/Number.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;
using namespace cv;
using namespace ml;


int main() {
    string readRoot = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/number_pkg/src/SVM_img/";
    string saveRoot = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/SVM.xml";
    Number number(readRoot, saveRoot);
    number.start();
    return 0;
}