#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"

using namespace std;

void call_back(sensor_msgs::Image imgInfo) {
    cv_bridge::CvImagePtr cvPtr = cv_bridge::toCvCopy(imgInfo, sensor_msgs::image_encodings::TYPE_8UC3);
    cv::Mat cvImg = cvPtr->image;
    if (!cvImg.empty()) {
        cout << cvImg.type() << endl;
    }
    cv::imshow("Test", cvImg);
    cv::destroyAllWindows();
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "receive_pkg_node");
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("Driver_Node", 1, call_back);
    
    while (ros::ok()) {
        ros::spinOnce();
    }
    return 0;
}
