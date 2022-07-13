//
// Created by wjy on 22-7-13.
//
#ifndef SRC_IMGPUBLISHER_H
#define SRC_IMGPUBLISHER_H

#include <utility>

#include "BasePublisher.h"
#include "iostream"
#include "opencv2/core/core.hpp"
#include "ros/ros.h"
#include "sensor_msgs/Image.h"


using namespace std;
using namespace cv;
using namespace ros;


class ImgPublisher : public BasePublisher {
private:
    //��������
    string topic;
    //������
    Publisher publisher;
    //�ڵ㴦����
    NodeHandle nodeHandle;
    //��Ϣͼ��ָ��
    sensor_msgs::ImagePtr msg;
    //����Ƶ��
    Rate rate;
protected:
    //ͼƬ����ת��
    bool imgConvert(Mat& cvImg) override;
public:
    //������
    ImgPublisher(string inputTopic, int rate) : topic(move(inputTopic)), rate(rate) {}
    //������Ϣ
    void publish(Mat& inputImg) override;
};

#endif //SRC_IMGPUBLISHER_H
