#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "ros/ros.h"
#include "MVReceiver.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    //³õÊ¼»¯ros
    init(argc,argv,"receive_pkg_node");
    MVReceiver mvReceiver;
    mvReceiver.subscribe();
    //Ë¢ÐÂ
    ros::spin();
    return 0;
}