//
// Created by wjy on 22-7-9.
//

#ifndef SRC_MVRECEIVER_H
#define SRC_MVRECEIVER_H
#include "BaseReceiver.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"

using namespace std;
using namespace cv;
using namespace ros;

class MVReceiver : public BaseReceiver {
private:
    NodeHandle nodeHandle;
    Subscriber subscriber;
protected:
    /**
     * @brief subscrib的回调函数
     */
    static void callBack(const sensor_msgs::Image::ConstPtr& imgInfo);
public:
    /**
     * @brief 订阅话题
     */
    void subscribe() override;
};


#endif //SRC_MVRECEIVER_H
