//
// Created by wjy on 22-7-10.
//

#ifndef SRC_RANGER_H
#define SRC_RANGER_H

#include "opencv2/core.hpp"
#include "receive_pkg/Int32Receiver.h"

using namespace std;
using namespace cv;

//工具类:解算PnP,不可被实例化
class Ranger {
private:
    //指向当前对象的静态指针
    static Ranger* pThis;
    //相机内参矩阵
    Mat cameraMatrix;
    //畸变矩阵
    Mat disCoeffs;
    //装甲板灯条的点以及中心点
    Point2f *points{};
    //装甲板的宽高
    float imageWidth{};
    float imageHeight{};
    //装甲板的实际宽度和高度
    static float boardWidth;
    static float boardHeight;
    //从solvePnP返回的旋转向量和平移向量
    Mat rvecCamera2Obj, tvecCamera2Obj;
    //平移矩阵的三个数
    float tx{}, ty{}, tz{};
    //相机到目标点的距离
    float distObj2Camera{};
    //透视变换所需要的角点
    Point2f pointsOfROI[4], pointsOfNumber[4];
    //接收器
    Int32Receiver int32Receiver;
    /**
     * @brief 初始化成员变量
     */
    void init(const RotatedRect& a, const RotatedRect& b);

    /**
     * @brief 调整点的顺序
     * @param angle 左灯条角度
     * @param pointsA 左灯条四个点
     * @param pointsB 右灯条四个点
     */
    void adjustTheOrderOfPoints(float angle, Point2f pointsA[4], Point2f pointsB[4]);

    /**
     * @brief 计算世界坐标
     * @return 世界坐标
     */
    vector<Point3f> getObjPoints();

    /**
     * @brief 计算装甲板图片的长宽
     */
    void calculateTheSizeOfImage();

    /**
     * @brief 误差计算
     */
    void caculateError();
    /**
     * @brief 单目测距
     * @param rvecCamera2Obj 从相机坐标系到世界坐标系的旋转向量
     * @param tvecCamera2Obj 从相机坐标系到世界坐标系的平移向量
     * @param demo 原图
     */
    void distanceSolver(Mat& demo);
    /**
     * @brief 计算欧拉角
     * @param demo 原图
     */
    void eulerSolver(Mat& demo);
public:
    /**
     * @brief 开始解算PnP
     * @param a 矩形a
     * @param b 矩形b
     */
    void start(const RotatedRect& a, const RotatedRect& b, Mat& demo);

    /**
     * @brief 获取装甲板ROI图像
     * @param demo 原图
     * @return 装甲板ROI区域
     */
    Mat getROI(Mat& demo);
    /**
     * @brief 构造器
     * @param CM 相机内参矩阵
     * @param DC 相机畸变矩阵
     */

    /**
    * @brief 设置装甲板尺寸
    * @param number 装甲板数字
    */
    static void setBoardSize(int number = 4);

    Ranger(Mat& CM, Mat& DC) : cameraMatrix(CM), disCoeffs(DC) ,int32Receiver("NumberBack") {};

    ~Ranger() = default;
};


#endif //SRC_RANGER_H
