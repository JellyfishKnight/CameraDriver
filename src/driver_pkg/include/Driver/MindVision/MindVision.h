#ifndef MINDVISION_H
#define MINDVISION_H


#include "CameraApi.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>
#include "BaseDriver.h"



class MindVision : public BaseDriver{
private:
    int hCamera;                            //相机句柄
    int CameraCounts = 4;                  //相机数量
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
    MindVision() = default;

    ~MindVision() = default;
    /**
     * @brief 初始化
     * 
     * @return true 初始化成功
     * @return false 初始化失败
     */
    bool init() override;
    /**
     * @brief 启动相机
     * 
     * @return true 启动成功
     * @return false 启动失败
     */
    bool start() override;
    /**
     * @brief 关闭相机
     * 
     * @return true 关闭成功
     * @return false 关闭失败
     */
    bool stop() override;
    /**
     * @brief 将相机的数据转化为Mat
     * 
     * @return true 转化成功
     * @return false 转化失败
     */
    bool grab(cv::Mat& src) override;
};

#endif //MINDVISION_H