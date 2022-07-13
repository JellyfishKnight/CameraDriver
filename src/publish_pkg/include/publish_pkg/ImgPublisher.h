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
    //话题名称
    string topic;
    //发布器
    Publisher publisher;
    //节点处理器
    NodeHandle nodeHandle;
    //消息图像指针
    sensor_msgs::ImagePtr msg;
    //发布频率
    Rate rate;
protected:
    //图片类型转换
    bool imgConvert(Mat& cvImg) override;
public:
    //构造器
    ImgPublisher(string inputTopic, int rate) : topic(move(inputTopic)), rate(rate) {}
    //发布消息
    void publish(Mat& inputImg) override;
};

#endif //SRC_IMGPUBLISHER_H
