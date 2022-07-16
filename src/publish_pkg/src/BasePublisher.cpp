//
// Created by wjy on 22-7-13.
//
#include "publish_pkg/BasePublisher.h"
#include "iostream"

using namespace std;


void BasePublisher::publish(cv::Mat &inputImg) {
    cout << "Base Publish" << endl;
}

bool BasePublisher::imgConvert(cv::Mat cvImg) {
    cout << "Base Image Convert" << endl;
    return true;
}

bool BasePublisher::NumberConvert(int inputNumber) {
    cout << "Base NUmber Convert" << endl;
    return true;
}

void BasePublisher::publish(int number) {
    cout << "Base Int32 Publish" << endl;
}