#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "boost/bind.hpp"
#include "sensor_msgs/Image.h"
#include "iostream"

using namespace std;


void call_back(sensor_msgs::Image::ConstPtr imgInfo, cv::Mat* cvImg) {
    cv_bridge::CvImagePtr cvPtr = cv_bridge::toCvCopy(*imgInfo, sensor_msgs::image_encodings::TYPE_8UC3);
    *cvImg = cvPtr->image;
    // cout << cvImg.channels() << endl;
    cv::imshow("demo", *cvImg);
    cv::waitKey(1);
    // while (true) {
    //     int c = cv::waitKey(1);
    //     if (c == 27) {
    //         break;
    //     }
    // }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "receive_pkg_node");
    ros::NodeHandle nh;
    cv::Mat cvImg;
    ros::Subscriber sub = nh.subscribe<sensor_msgs::Image>("Driver_Node", 1, boost::bind(&call_back, _1, &cvImg));
    cv::Mat demo = cvImg.clone();
    while (ros::ok()) {
        ros::spinOnce();
    }
    cv::waitKey(0);
    return 0;
}
