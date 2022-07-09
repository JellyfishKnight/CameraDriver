//
// Created by wjy on 22-7-9.
//

#ifndef SRC_BASERECEIVER_H
#define SRC_BASERECEIVER_H
#include "opencv2/core/core.hpp"
#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"

using namespace cv;

class BaseReceiver {
public:
    virtual void subscribe() = 0;
    virtual Mat getImg() = 0;
};



#endif //SRC_BASERECEIVER_H
