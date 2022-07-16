//
// Created by wjy on 22-7-16.
//

#ifndef SRC_INT32RECEIVER_H
#define SRC_INT32RECEIVER_H
#include "ros/ros.h"
#include "std_msgs/Int32.h"

using namespace std;
using namespace ros;


class Int32Receiver{
private:
    //��������
    string topic;
    //�ڵ㴦����
    NodeHandle nodeHandle;
    //������
    Subscriber subscriber;
    //int����number
    int number;
    //ָ��ǰ�����ľ�ָ̬��
    static Int32Receiver* pThis;
    /**
     * @brief �ص�����
     * @param inputNumber ���ܵ�����Ϣ
     * @param p ����ָ��
     */
    static void callBack(const std_msgs::Int32::ConstPtr& inputNumber, void (*p)(int out));
public:
    /**
     * @brief ����
     * @param p ����ָ��
     */
    void subscribe(void (*p)(int out));
};
#endif //SRC_INT32RECEIVER_H
