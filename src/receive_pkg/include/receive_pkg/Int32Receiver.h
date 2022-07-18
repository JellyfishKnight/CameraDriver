//
// Created by wjy on 22-7-16.
//

#ifndef SRC_INT32RECEIVER_H
#define SRC_INT32RECEIVER_H
#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "BaseReceiver.h"

using namespace std;
using namespace ros;


class Int32Receiver : public BaseReceiver {
private:
    //��������
    string topic;
    //�ڵ㴦����
    NodeHandle nodeHandle;
    //������
    Subscriber subscriber;
    //int����number
    int number{};
    //ָ��ǰ�����ľ�ָ̬��
    static Int32Receiver* pThis;
protected:
    /**
    * @brief �ص�����
    * @param inputNumber ���ܵ�����Ϣ
    * @param p ����ָ��
    */
    static void callBack(const std_msgs::Int32::ConstPtr& inputNumber, void (*p)(int out));


public:
    /**
     * @brief ������
     * @param topic ��������
     */
    explicit Int32Receiver(string topic) : topic(move(topic)) {
        pThis = this;
    }
    /**
     * @brief ����
     * @param p ����ָ��
     */
    void subscribe(void (*p)(int out)) override;

    ~Int32Receiver() {
        cout << "Int32Receiver" << endl;
    }
};


#endif //SRC_INT32RECEIVER_H
