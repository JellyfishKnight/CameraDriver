//
// Created by wjy on 22-7-9.
//

#ifndef SRC_BASERECEIVER_H
#define SRC_BASERECEIVER_H
#include "iostream"
#include "opencv2/core/core.hpp"
#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

class BaseReceiver {                //Ðé»ùÀà
protected:

public:
    BaseReceiver() {
        cout << "Base Receiver1" << endl;
    };
    ~BaseReceiver() {
        cout << "Base Receiver" << endl;
    }
    virtual void subscribe(void (*p)(Mat mask)) {
        cout << "Base Subscribe" << endl;
    }
    virtual void subscribe(void (*p)(int number)) {
        cout << "Base Subscribe" << endl;
    }
};


#endif //SRC_BASERECEIVER_H
