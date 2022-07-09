#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "ros/ros.h"
#include "MVReceiver.h"

using namespace std;
using namespace cv;

//void call_back(const sensor_msgs::Image::ConstPtr& imgInfo, cv::Mat& cvImg) {
//    cv_bridge::CvImagePtr cvPtr = cv_bridge::toCvCopy(*imgInfo, sensor_msgs::image_encodings::TYPE_8UC3);
//    cvImg = cvPtr->image;
//    cv::namedWindow("demo",cv::WINDOW_NORMAL);
//    cv::imshow("demo", cvImg);
//    cv::waitKey(1);
//}

int main(int argc, char *argv[])
{
    init(argc,argv,"receive_pkg_node");
    MVReceiver mvReceiver;
    Mat cvImg;
    mvReceiver.subscribe();
    cvImg = mvReceiver.getImg();
    while (ros::ok()) {
        if(!cvImg.empty()) {
            imshow("demo", cvImg);
            waitKey(1);
        }
        ros::spinOnce();
    }
    return 0;
}