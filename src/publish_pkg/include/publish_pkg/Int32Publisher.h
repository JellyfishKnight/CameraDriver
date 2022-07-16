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
    //��������
    string topic;
    //������
    Publisher publisher;
    //�ڵ㴦����
    NodeHandle nodeHandle;
    //�����͵�����
    std_msgs::Int32 number;
    //����Ƶ��
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
     * @brief ������
     * @param topic ��������
     * @param rate ����Ƶ��
     */
    Int32Publisher(string topic, int rate) : topic(move(topic)), rate(rate) {}
    /**
     * @brief ����������Ϣ
     * @param number �������͵�����
     */
    void publish(int inputNumber);
};

#endif //SRC_INT32PUBLISHER_H
