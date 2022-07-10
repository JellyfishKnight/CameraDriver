#include "iostream"
#include "MindVision.h"
#include "ros/ros.h"

using namespace std;



int main(int argc, char *argv[])
{
    //ros≥ı ºªØ
    ros::init(argc, argv, "driver_pkg_node");
    MindVision mindVision(10000);
    if (mindVision.init() && mindVision.start()) {
        mindVision.publish();
    } else {
        cout << "Init failed or start failed!" << endl;
        return -1;
    }
    mindVision.stop();
    return 0;
}
