//
// Created by wjy on 22-7-10.
//

#ifndef SRC_SYSTEM_H
#define SRC_SYSTEM_H

#include <utility>
#include "publish_pkg/ImgPublisher.h"
#include "PreProcess.h"
#include "Ranger.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "vector"

#define maxLenRatio 10

#define minLenRatio 3

#define maxAngleError 5

#define maxAreaRation 2

#define minImageRatio 0.5

#define maxImageRatio 2


using namespace std;
using namespace cv;

class System {
private:
    //静态指针指向当前对象
    static System* pThis;
    //视频路径 (也可以从相机接收)
    string root;
    //相机数据文件路径
    string dataRoot;
    //敌方颜色
    Color color;
    //相机内参矩阵以及畸变距阵
    Mat cameraMatrix, disCoeffs;
    //原图
    Mat demo;
    //二值化输出
    Mat binaryDst;
    //所有找到的轮廓
    vector<vector<Point>> allContours;
    //轮廓层级
    vector<Vec4i> hierarchy;
    //筛选过后的轮廓
    vector<vector<Point>> selectedContours;
    //所有被筛选过后的轮廓拟合的矩形
    vector<RotatedRect> allRects;
    //匹配上的两个矩形
    RotatedRect matchA, matchB;
    //装甲板中心
    Point center;
    //经过调整后的灯条角度
    float angleI{}, angleJ{};
    //帧率
    static float FPS;
    //接收器
//    Int32Receiver* int32Receiver{};
    //发布器
    ImgPublisher* imgPublisher{};
    //传给ROI区域获取的原图
    Mat ROINeeded;
    /**
     * @brief 数据读取
     * @return true 成功读取
     * @return false 读取失败
     */
    static bool DataRead();
    /**
     * @brief 找到轮廓并且进行筛选
     * @param frame 输入图像,应当为二值化图像
     */
    void ContoursFind(const Mat& frame);

    /**
     * @brief 拟合矩形并且进行匹配
     */
    void RectFit(Mat& src);

    /**
     * @brief 调整角度以方便运算
     * @param a 旋转矩形
     * @return 调整后的角度
     */
    float adjustAngle(const RotatedRect& a);

    /**
     * @brief 筛选装甲板区域
     * @param a
     * @param b
     * @return true 通过筛选
     * @return false 不通过筛选
     */
    bool selectionOfRects(const RotatedRect& a, const RotatedRect& b);

public:
    /**
     * @brief 构造器
     * @param r 视频输入路径
     * @param c 敌方装甲板颜色
     */
    explicit System(string  fr = "NULL", Color c = BLUE, string dr = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/CameraData.xml") :
    root(std::move(fr)), dataRoot(move(dr)), color(c) {
        pThis = this;
        DataRead();
        imgPublisher = new ImgPublisher("Number", 10000);
//        int32Receiver = new Int32Receiver("NumberBack");
    }

    /**
     * @brief 启动识别系统
     */
    static void Start(Mat demo);
    /**
     * @brief 重载函数,用于视频调试
     */
    static void Start();

    /**
     * @brief 析构器,释放内存
     */
    ~System() {
        delete imgPublisher;
//        delete int32Receiver;
    }

};



#endif //SRC_SYSTEM_H
