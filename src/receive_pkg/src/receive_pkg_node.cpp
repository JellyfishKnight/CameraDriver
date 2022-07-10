#include "ros/ros.h"
#include "MVReceiver.h"

using namespace std;
using namespace cv;

void showImg(Mat mask) {
    imshow("mask", mask);
    waitKey(1);
}

int main(int argc, char *argv[]) {
    //≥ı ºªØros
    init(argc,argv,"receive_pkg_node");
    MVReceiver mvReceiver;
    mvReceiver.subscribe(showImg);
    return 0;
}