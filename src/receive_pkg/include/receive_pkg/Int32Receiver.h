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
    //话题名称
    string topic;
    //节点处理器
    NodeHandle nodeHandle;
    //订阅器
    Subscriber subscriber;
    //int类型number
    int number{};
    //指向当前变量的静态指针
    static Int32Receiver* pThis;
protected:
    /**
    * @brief 回调函数
    * @param inputNumber 接受到的消息
    * @param p 函数指针
    */
    static void callBack(const std_msgs::Int32::ConstPtr& inputNumber, void (*p)(int out));


public:
    /**
     * @brief 构造器
     * @param topic 话题名称
     */
    explicit Int32Receiver(string topic) : topic(move(topic)) {
        pThis = this;
    }
    /**
     * @brief 订阅
     * @param p 函数指针
     */
    void subscribe(void (*p)(int out)) override;

    ~Int32Receiver() {
        cout << "Int32Receiver" << endl;
    }
};


#endif //SRC_INT32RECEIVER_H
