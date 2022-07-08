#include "CameraApi.h"
#include "opencv2/core.hpp"
#include "ros/ros.h"

using namespace cv;

class MindVision {
private:
    int hCamera;
    int iStatus = -1;
    int hCameraCounts = -1;
    int fps;
    tSdkCameraDevInfo tCameraEnumList;
    tSdkCameraCapbility tCapability;
    tSdkFrameHead sFrameInfo;
    BYTE* pbyBuffer;


public:
    MindVision();

    ~MindVision();

    void init();

    void work();

    void transport();

};