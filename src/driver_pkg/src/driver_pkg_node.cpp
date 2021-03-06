#include "iostream"
#include "driver_pkg/MindVision.h"
#include "ros/ros.h"

using namespace std;



int main(int argc, char *argv[])
{
    //ros??ʼ??
    ros::init(argc, argv, "driver_pkg_node");
    MindVision mindVision("Driver_Node", 10000);
    if (mindVision.init() && mindVision.start()) {
        mindVision.publish();
    } else {
        cout << "Init failed or start failed!" << endl;
        return -1;
    }
    mindVision.stop();
    return 0;
}
