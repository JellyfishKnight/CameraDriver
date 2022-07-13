//
// Created by wjy on 22-7-9.
//

#include "receive_pkg/MVReceiver.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"

using namespace cv;
using namespace ros;

MVReceiver* MVReceiver::pThis = nullptr;

void MVReceiver::callBack(const sensor_msgs::Image::ConstPtr &imgInfo, void (*p)(Mat mask)) {
    //接收message
    cv_bridge::CvImagePtr cvPtr = cv_bridge::toCvCopy(*imgInfo, sensor_msgs::image_encodings::TYPE_8UC3);
    //将接收到的数据转化为Mat
    pThis->cvImg = cvPtr->image;
    //将参数传出
    p(pThis->cvImg);
}

void MVReceiver::subscribe(void (*p)(Mat mask)) {
    //订阅话题
    subscriber = nodeHandle.subscribe<sensor_msgs::Image>(topic, 1, bind(&callBack, _1, p));
    spin();
}