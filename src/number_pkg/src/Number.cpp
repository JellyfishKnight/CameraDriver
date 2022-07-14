//
// Created by wjy on 22-7-11.
//
#include "number_pkg/Number.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/ml.hpp"

#include <iostream>
#include <random>

using namespace std;
using namespace cv;
using namespace ml;


Number* Number::pThis = nullptr;

void Number::start(Mat numberImage) {
    //格式转换
    Mat maskOfReshape;
    Mat channels[3];
    split(numberImage, channels);
    numberImage = channels[0] - channels[2];
    threshold(numberImage, numberImage, 10, 255, THRESH_BINARY);
    namedWindow("Number",WINDOW_NORMAL);
    imshow("Number", numberImage);
    waitKey(1);
    numberImage.reshape(0, 1).convertTo(maskOfReshape, CV_32F, 1.0 / 255);
    Mat testImage;
    maskOfReshape.convertTo(testImage, CV_32F, 1.0 / 255);
    //使用未经初始化的实例载入模型
    Ptr<SVM> svm = StatModel::load<SVM>(pThis->readRoot);
    //判空
    if (svm.empty()) {
        cout << "SVM load failed!" << endl;
        return ;
    }
    int number = lround(svm->predict(maskOfReshape));
    cout << "Number: " << number << endl;
}
