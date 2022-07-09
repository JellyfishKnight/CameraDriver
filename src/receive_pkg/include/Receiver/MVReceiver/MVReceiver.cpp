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

cv_bridge::CvImagePtr MVReceiver::cvPtr;


void MVReceiver::callBack(const sensor_msgs::Image::ConstPtr& imgInfo) {
    cvPtr = cv_bridge::toCvCopy(*imgInfo, sensor_msgs::image_encodings::TYPE_8UC3);
//    imshow("sss",cvImg);
//    waitKey(1);
}

void MVReceiver::subscribe() {
    subscriber = nodeHandle.subscribe("Driver_Node" ,1 ,callBack);
}

Mat MVReceiver::getImg() {
    return cvPtr->image;
}