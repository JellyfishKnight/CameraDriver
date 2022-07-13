//
// Created by wjy on 22-7-13.
//

#ifndef SRC_BASEPUBLISHER_H
#define SRC_BASEPUBLISHER_H

#include "opencv2/core/core.hpp"

class BasePublisher {   //Ðé»ùÀà
protected:
    virtual bool imgConvert(cv::Mat cvImg) = 0;
public:
    virtual void publish(cv::Mat& inputImg) = 0;
};


#endif //SRC_BASEPUBLISHER_H
