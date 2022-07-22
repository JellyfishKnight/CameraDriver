//
// Created by wjy on 22-7-22.
//
#include "recognize_pkg/Number.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;
using namespace ml;



int Number::start(Mat numberImage) {
    /*��ʽת��*/
    //ͨ������
    split(numberImage, channels);
    numberImage = channels[0] - channels[2];
    //��ֵ��
    threshold(numberImage, numberImage, 10, 255, THRESH_BINARY);
    //��ʾͼ��
//    namedWindow("Number",WINDOW_NORMAL);
//    imshow("Number", numberImage);
//    waitKey(1);
    //�ع�ͼƬ��С�Լ�����
    numberImage.reshape(0, 1).convertTo(maskOfReshape, CV_32F, 1.0 / 255);
    maskOfReshape.convertTo(testImage, CV_32F, 1.0 / 255);
    //�п�
    if (svm.empty()) {
        cout << "SVM load failed!" << endl;
        return 0;
    }
    return lround(svm->predict(maskOfReshape));
}
