//
// Created by wjy on 22-7-11.
//
#include "number_pkg/Number.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace std;
using namespace cv;
using namespace ml;


Number* Number::pThis = nullptr;

void Number::start(Mat numberImage) {
    /*��ʽת��*/
    //ͨ������
    split(numberImage, pThis->channels);
    numberImage = pThis->channels[0] - pThis->channels[2];
    //��ֵ��
    threshold(numberImage, numberImage, 10, 255, THRESH_BINARY);
    //��ʾͼ��
    namedWindow("Number",WINDOW_NORMAL);
    imshow("Number", numberImage);
    waitKey(1);
    //�ع�ͼƬ��С�Լ�����
    numberImage.reshape(0, 1).convertTo(pThis->maskOfReshape, CV_32F, 1.0 / 255);
    pThis->maskOfReshape.convertTo(pThis->testImage, CV_32F, 1.0 / 255);
    //�п�
    if (pThis->svm.empty()) {
        cout << "SVM load failed!" << endl;
        return ;
    }
    int number = lround(pThis->svm->predict(pThis->maskOfReshape));
    pThis->int32Publisher.publish(number);
}
