#ifndef MINDVISION_H
#define MINDVISION_H


#include "CameraApi.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>
#include "BaseDriver.h"
#include "ros/ros.h"
#include "sensor_msgs/Image.h"

using namespace ros;
using namespace cv;

class MindVision : public BaseDriver{
private:
    int hCamera{};                            //相机句柄
    int CameraCounts = 4;                  //相机数量
    int fps{};
    tSdkCameraDevInfo CameraEnumList{};       //相机枚举列表
    tSdkCameraCapbility Capability{};         //设备描述信息
    tSdkFrameHead FrameInfo{};
    BYTE* pbyBuffer{};
    int iDisplayFrames = 10000;
    IplImage* ilpImage = nullptr;
    double* pfLineTime{};
    int channel = 3;
    unsigned char* g_pRgBuffer{};              //处理后数据缓存区
    Mat src;                                //cv图像

    NodeHandle nodeHandle;                  //节点处理器
    Publisher publisher;                    //发布器
    sensor_msgs::ImagePtr msg;              //消息图像指针

    Rate rate;                              //发送频率
protected:
    /**
     * @brief 设置相机参数
     */
    void setCameraData() override;
    /**
     * @brief 将相机的数据转化为Mat
     *
     * @return true 转化成功
     * @return false 转化失败
     */
    bool grab() override;
public:
    /**
     * @brief 构造函数
     * @param frequency 发送频率(每秒多少次)
     */
    explicit MindVision(int frequency = 10000) : rate(frequency) {}

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
     * @brief 发布消息
     */
    void publish() override;
};

#endif //MINDVISION_H