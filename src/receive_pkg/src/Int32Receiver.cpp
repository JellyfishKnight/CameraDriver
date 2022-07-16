//
// Created by wjy on 22-7-16.
//
#include "receive_pkg/Int32Receiver.h"
#include "ros/ros.h"
#include "std_msgs/Int32.h"

using namespace std;
using namespace ros;

void Int32Receiver::callBack(const std_msgs::Int32::ConstPtr& inputNumber, void (*p)(int)) {
    //转换数据类型
    pThis->number = inputNumber->data;
    //传出参数
    p(pThis->number);
}

void Int32Receiver::subscribe(void (*p)(int out)) {
    //订阅节点
    subscriber = nodeHandle.subscribe<std_msgs::Int32>(topic, 1, bind(&callBack, _1, p));
    spinOnce();
}