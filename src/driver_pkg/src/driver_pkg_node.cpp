#include "iostream"
#include "MindVision.h"
#include "BaseDriver.h"
#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "driver_pkg_node");
    MindVision mindVision;
    cv::Mat msgPicture;
    sensor_msgs::ImagePtr msg;
    ros::NodeHandle nodeHandle;
    ros::Publisher publisher = nodeHandle.advertise<sensor_msgs::Image>("Driver_Node", 1);
    if (mindVision.init() && mindVision.start()) {
        while (ros::ok()) {
            mindVision.grab(msgPicture);
            if (msgPicture.empty()) {
                cout << "Grab failed!" << endl;
                return -1;
            }
            cout << "Sending" << endl;
            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", msgPicture).toImageMsg();
            publisher.publish(*msg);
        }
    } else {
        cout << "Initialize or start failed" << endl;
        return -1;
    }
    return 0;
}
