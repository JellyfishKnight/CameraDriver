#ifndef MINDVISION_H
#define MINDVISION_H


#include "CameraApi.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>
#include "BaseDriver.h"



class MindVision : public BaseDriver{
private:
    int hCamera;                            //相机句柄
    int CameraCounts = -1;                  //相机数量
    int fps;                        
    tSdkCameraDevInfo CameraEnumList;       //相机枚举列表
    tSdkCameraCapbility Capability;         //设备描述信息
    tSdkFrameHead FrameInfo;
    BYTE* pbyBuffer;
    int iDisplayFrames = 10000;
    IplImage* ilpImage = nullptr;
    double* pfLineTime;
    int channel = 3;
    unsigned char* g_pRgBuffer;              //处理后数据缓存区

protected:
    /**
     * @brief 设置相机参数
     */
    void setCameraData() override;                    

public:
    MindVision() ;

    ~MindVision();
    /**
     * @brief 初始化
     * 
     * @return true 初始化成功
     * @return false 初始化失败
     */
    bool init() override;

    void work() ;

    void transport();

};

#endif //MINDVISION_H