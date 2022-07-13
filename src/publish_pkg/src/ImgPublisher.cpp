//
// Created by wjy on 22-7-13.
//
#include "publish_pkg/ImgPublisher.h"
#include "ros/ros.h"
#include "opencv2/core/core.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"

using namespace cv;
using namespace ros;

bool ImgPublisher::imgConvert(Mat& cvImg) {
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cvImg).toImageMsg();
}

void ImgPublisher::publish(Mat& inputImg) {
    imgConvert(inputImg);
    publisher.publish(msg);
    rate.sleep();
}