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
    //����message
    cv_bridge::CvImagePtr cvPtr = cv_bridge::toCvCopy(*imgInfo, sensor_msgs::image_encodings::TYPE_8UC3);
    //�����յ�������ת��ΪMat
    pThis->cvImg = cvPtr->image;
    //����������
    p(pThis->cvImg);
}

void MVReceiver::subscribe(void (*p)(Mat mask)) {
    //���Ļ���
    subscriber = nodeHandle.subscribe<sensor_msgs::Image>(topic, 1, bind(&callBack, _1, p));
    spin();
}