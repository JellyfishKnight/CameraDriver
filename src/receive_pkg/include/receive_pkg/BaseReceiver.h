//
// Created by wjy on 22-7-9.
//

#ifndef SRC_BASERECEIVER_H
#define SRC_BASERECEIVER_H
#include "opencv2/core/core.hpp"
#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"
#include "opencv2/core/core.hpp"

using namespace cv;

class BaseReceiver {                //Ðé»ùÀà
public:
    virtual void subscribe(void (*p)(Mat mask));
    virtual void subscribe(void (*p)(int number));
};



#endif //SRC_BASERECEIVER_H
