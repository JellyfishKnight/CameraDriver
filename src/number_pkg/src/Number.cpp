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
    //��ʽת��
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
    //ʹ��δ����ʼ����ʵ������ģ��
    Ptr<SVM> svm = StatModel::load<SVM>(pThis->readRoot);
    //�п�
    if (svm.empty()) {
        cout << "SVM load failed!" << endl;
        return ;
    }
    int number = lround(svm->predict(maskOfReshape));
    cout << "Number: " << number << endl;
}
