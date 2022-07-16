//
// Created by wjy on 22-7-13.
//

#ifndef SRC_BASEPUBLISHER_H
#define SRC_BASEPUBLISHER_H

#include "opencv2/core/core.hpp"

class BasePublisher {   //Ðé»ùÀà
protected:
    virtual bool imgConvert(cv::Mat cvImg);
    virtual bool NumberConvert(int inputNumber);
public:
    virtual void publish(cv::Mat& inputImg);
    virtual void publish(int number);
};


#endif //SRC_BASEPUBLISHER_H
