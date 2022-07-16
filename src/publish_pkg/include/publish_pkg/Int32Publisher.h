//
// Created by wjy on 22-7-16.
//

#ifndef SRC_INT32PUBLISHER_H
#define SRC_INT32PUBLISHER_H


#include "std_msgs/Int32.h"
#include "ros/ros.h"
#include "string"

using namespace std;
using namespace ros;


class Int32Publisher {
private:
    //话题名称
    string topic;
    //发布器
    Publisher publisher;
    //节点处理器
    NodeHandle nodeHandle;
    //被发送的数字
    std_msgs::Int32 number;
    //发布频率
    Rate rate;
protected:
    /**
     * @brief
     * @param number
     * @return
     */
    bool NumberConvert(int inputNumber);
public:
    /**
     * @brief 构造器
     * @param topic 话题名称
     * @param rate 发送频率
     */
    Int32Publisher(string topic, int rate) : topic(move(topic)), rate(rate) {}
    /**
     * @brief 发布数字消息
     * @param number 将被发送的数字
     */
    void publish(int inputNumber);
};

#endif //SRC_INT32PUBLISHER_H
