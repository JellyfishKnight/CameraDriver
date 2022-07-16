//
// Created by wjy on 22-7-16.
//

#include "publish_pkg/Int32Publisher.h"

bool Int32Publisher::NumberConvert(int inputNumber) {
    number.data = inputNumber;
    return true;
}

void Int32Publisher::publish(int inputNumber) {
    publisher = nodeHandle.advertise<std_msgs::Int32>(topic, 1);
    if (NumberConvert(inputNumber)) {
        publisher.publish(number);
        rate.sleep();
    }
}