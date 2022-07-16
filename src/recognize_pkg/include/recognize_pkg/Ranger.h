//
// Created by wjy on 22-7-10.
//

#ifndef SRC_RANGER_H
#define SRC_RANGER_H

#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

//工具类:解算PnP,不可被实例化
class Ranger {
private:
    //相机内参矩阵
    Mat cameraMatrix;
    //畸变矩阵
    Mat disCoeffs;
    //装甲板灯条的点以及中心点
    Point2f *points;
    //装甲板的实际宽度和高度
    float boardWidth = 135;
    float boardHeight = 125;
    //从solvePnP返回的旋转向量和平移向量
    Mat rvecCamera2Obj, tvecCamera2Obj;
    //平移矩阵的三个数
    float tx, ty, tz;
    //相机到目标点的距离
    float distObj2Camera;
    //透视变换所需要的角点
    Point2f pointsOfROI[4], pointsOfNumber[4];
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

    Ranger(Mat& CM, Mat& DC) : cameraMatrix(CM), disCoeffs(DC) {};

    ~Ranger() = default;
};


#endif //SRC_RANGER_H
