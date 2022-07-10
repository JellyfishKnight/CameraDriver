//
// Created by wjy on 22-7-9.
//

#include "MVReceiver.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"

using namespace cv;
using namespace ros;

MVReceiver* MVReceiver::pThis = nullptr;

void MVReceiver::callBack(const sensor_msgs::Image::ConstPtr &imgInfo) {
    //接收message
    cv_bridge::CvImagePtr cvPtr = cv_bridge::toCvCopy(*imgInfo, sensor_msgs::image_encodings::TYPE_8UC3);
    //将接收到的数据转化为Mat
    pThis->cvImg = cvPtr->image;
    imshow("cvImg",pThis->cvImg);
    waitKey(1);
}

void MVReceiver::subscribe() {
    //订阅话题
    subscriber = nodeHandle.subscribe("Driver_Node", 1, callBack);
    //刷新
    spin();
}