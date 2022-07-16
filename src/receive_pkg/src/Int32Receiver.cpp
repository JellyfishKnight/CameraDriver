//
// Created by wjy on 22-7-16.
//
#include "receive_pkg/Int32Receiver.h"
#include "ros/ros.h"
#include "std_msgs/Int32.h"

using namespace std;
using namespace ros;

void Int32Receiver::callBack(const std_msgs::Int32::ConstPtr& inputNumber, void (*p)(int)) {
    //ת����������
    pThis->number = inputNumber->data;
    //��������
    p(pThis->number);
}

void Int32Receiver::subscribe(void (*p)(int out)) {
    //���Ľڵ�
    subscriber = nodeHandle.subscribe<std_msgs::Int32>(topic, 1, bind(&callBack, _1, p));
    spinOnce();
}