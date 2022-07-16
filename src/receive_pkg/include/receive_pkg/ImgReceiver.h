//
// Created by wjy on 22-7-9.
//

#ifndef SRC_IMGRECEIVER_H
#define SRC_IMGRECEIVER_H
#include "BaseReceiver.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"

using namespace std;
using namespace cv;
using namespace ros;



class ImgReceiver : BaseReceiver{
private:
    string topic;
    NodeHandle nodeHandle;
    Subscriber subscriber;
    Mat cvImg;
    static ImgReceiver* pThis;
protected:
    /**
     * @brief subscribe的回调函数
     */
    static void callBack(const sensor_msgs::Image::ConstPtr& imgInfo, void (*p)(Mat mask));
public:
    explicit ImgReceiver(string t) : topic(move(t)) {
        pThis = this;
    }
    /**
     * @brief 订阅话题
     * @param 函数指针,用于传参
     */
    void subscribe(void (*p)(Mat mask)) override;
};


#endif //SRC_IMGRECEIVER_H
