#include "ros/ros.h"
#include "MVReceiver.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    //��ʼ��ros
    init(argc,argv,"receive_pkg_node");
    MVReceiver mvReceiver;
    mvReceiver.subscribe();
    return 0;
}