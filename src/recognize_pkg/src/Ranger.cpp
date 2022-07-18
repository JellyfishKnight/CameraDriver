//
// Created by wjy on 22-7-10.
//
#include <iostream>
#include "recognize_pkg/Ranger.h"
#include "Eigen/Eigen"
#include "opencv2/core/eigen.hpp"
#include "recognize_pkg/DataReader.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;


float Ranger::boardWidth = 135;

float Ranger::boardHeight = 125;

/*调试完毕*/
void Ranger::init(const RotatedRect& a, const RotatedRect& b) {
    //标定的数据读取
    DataReader dataReader("/home/wjy/Projects/RMlearning/CameraDriverWS/src/recognize_pkg/data/data.xml");
    dataReader.readData(cameraMatrix, disCoeffs);
    Point2f pointA[4], pointB[4];
    a.points(pointA);
    b.points(pointB);
    points = new Point2f[9];
    Point2f center((a.center.x + b.center.x) / 2.0, (a.center.y + b.center.y) / 2.0);
    points[0] = center;
    adjustTheOrderOfPoints(a.angle, pointA, pointB);
}

void Ranger::adjustTheOrderOfPoints(float angle, Point2f pointsA[4], Point2f pointsB[4]) {
    //保证数据的对齐
    if (angle > 90) {
        points[1] = pointsA[3];
        points[2] = pointsA[0];
        points[3] = pointsB[3];
        points[4] = pointsB[0];
        points[5] = pointsB[1];
        points[6] = pointsB[2];
        points[7] = pointsA[1];
        points[8] = pointsA[2];
    } else {
        points[1] = pointsA[1];
        points[2] = pointsA[2];
        points[3] = pointsB[1];
        points[4] = pointsB[2];
        points[5] = pointsB[3];
        points[6] = pointsB[0];
        points[7] = pointsA[3];
        points[8] = pointsA[0];
    }
}


/*调试完毕*/
vector<Point3f> Ranger::getObjPoints() {
    //规范边界,防止数值越界
    calculateTheSizeOfImage();
    vector<Point3f> objPoints;
    Point3f temp(0, 0, 0);
    objPoints.push_back(temp);
    //解算每个点在世界坐标系中的坐标
    for (int i = 1; i < 9; i++) {
        temp.x = (points[i].x - points[0].x) / imageWidth * boardWidth;
        temp.y = (points[i].y - points[0].y) / imageHeight * boardHeight;
        objPoints.push_back(temp);
    }
    return objPoints;
}

void Ranger::calculateTheSizeOfImage() {
    float maxRight = 0, minLeft = INFINITY, maxDown = 0, minUp = INFINITY;
    //规范边界,防止数值越界
    for (int i = 0; i < 9; i++) {
        if (maxRight < points[i].x) {
            maxRight = points[i].x;
        }
        if (minLeft > points[i].x) {
            minLeft = points[i].x;
        }
        if (maxDown < points[i].y) {
            maxDown = points[i].y;
        }
        if (minUp > points[i].y) {
            minUp = points[i].y;
        }
    }
    //计算图像中装甲板的长宽
    imageWidth = maxRight - minLeft;
    imageHeight = maxDown - minUp;
}


/*调试完毕*/
void Ranger::caculateError() {
    vector<Point3f> objPoints = getObjPoints();
    vector<Point2f> outPutPoints;                       //3d到2d重投影
    projectPoints(objPoints, rvecCamera2Obj, tvecCamera2Obj, cameraMatrix, disCoeffs, outPutPoints);
    Mat test = Mat::zeros(Size(2000,2000), CV_8UC1);
    float totalError = 0;
    for (int i = 0; i < outPutPoints.size(); i++) {
        totalError += sqrt(pow((points[i].x - outPutPoints[i].x), 2) + pow((points[i].y - outPutPoints[i].y), 2));
    }
    totalError /= 9;
    cout << "Average error is : " << totalError << endl;
}

void Ranger::distanceSolver(Mat &demo) {     //将旋转向量转化为
    Mat rotRvec;
    Rodrigues(rvecCamera2Obj, rotRvec);                     //旋转矩阵
    //将opencv矩阵转化为Eigen的矩阵,方便矩阵运算
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> RMatrix;
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> TMatrix;
    cv2eigen(rotRvec, RMatrix);
    cv2eigen(tvecCamera2Obj, TMatrix);
    Eigen::Vector3f cameraPoint;
    //求解相机在世界坐标系中的坐标
    //cameraPoint = -RMatrix.inverse() * TMatrix;
    //算出相机到装甲板中心的距离
    tx = tvecCamera2Obj.at<double>(0);
    ty = tvecCamera2Obj.at<double>(1);
    tz = tvecCamera2Obj.at<double>(2);
    distObj2Camera = sqrt(tx * tx + ty * ty + tz * tz);
    //在图上标出装甲板的距离
    putText(demo,"Dist:" + to_string(distObj2Camera).substr(0, 6), points[4], FONT_HERSHEY_SIMPLEX,0.5, Scalar(0,255,0),2);
}

void Ranger::eulerSolver(Mat &demo) {
    //俯仰角,水平转动角
    double pitch, yaw;
    yaw = atan2(tvecCamera2Obj.at<double>(0), tvecCamera2Obj.at<double>(2));
    pitch = -atan2(tvecCamera2Obj.at<double>(1),sqrt(tvecCamera2Obj.at<double>(0) * tvecCamera2Obj.at<double>(0) + tvecCamera2Obj.at<double>(2) * tvecCamera2Obj.at<double>(2)));
    //从弧度转化为角度
    yaw *= 180.0 / CV_PI;
    pitch *= 180.0 / CV_PI;
    cout << "Yaw: " << yaw << endl;
    cout << "Pitch: " << pitch << endl;
    putText(demo, "yaw" + to_string(yaw).substr(0, 4), points[1], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0,255), 2);
    putText(demo, "pitch:" + to_string(pitch).substr(0, 4), points[8], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 2);
}

/**
 * @brief 通过接收数字识别器传回的数字规范装甲板尺寸
 * @param number 装甲板编号
 */
void Ranger::setBoardSize(int number) {
    switch (number) {
        case 1:
            Ranger::boardWidth = 230;
            Ranger::boardHeight = 127;
            break;
        case 2:
        case 3:
        case 4:
            Ranger::boardWidth = 135;
            Ranger::boardHeight = 125;
            break;
        case 5:
        case 6:
        case 7:
            Ranger::boardWidth = 230;
            Ranger::boardHeight = 127;
        default:
            Ranger::boardWidth = 135;
            Ranger::boardHeight = 125;
            break;
    }
    cout << number << endl;
}

Mat Ranger::getROI(Mat& demo) {
    //指定ROI区域的四个角点
    pointsOfROI[0] = Point2f(points[1].x + 10, points[1].y - 10);
    pointsOfROI[1] = Point2f(points[4].x - 10, points[4].y - 10);
    pointsOfROI[2] = Point2f(points[5].x - 10, points[5].y + 10);
    pointsOfROI[3] = Point2f(points[8].x + 10, points[8].y + 10);
    //保证数据的对齐
    pointsOfNumber[0] = Point2f(0, 0);
    pointsOfNumber[1] = Point2f(demo.cols, 0);
    pointsOfNumber[2] = Point2f(demo.cols, demo.rows);
    pointsOfNumber[3] = Point2f(0, demo.rows);
    Mat ROI;
    //获取透视变换矩阵
    Mat tranMat = getPerspectiveTransform(pointsOfROI, pointsOfNumber);
    warpPerspective(demo, ROI, tranMat, ROI.size());
    //规范数据发送格式,使其能够被预测
    resize(ROI, ROI, Size(20, 20));
    return ROI;
}

void Ranger::start(const RotatedRect& a, const RotatedRect& b, Mat& demo) {        /**剩余的解算欧拉角暂时没有解决**/
    //初始化
    init(a, b);

    //获取世界坐标系点
    vector<Point3f> objPoints = getObjPoints();
    vector<Point2f> imgPoints(points, points + 9);

    //解算PnP
    solvePnP(objPoints, imgPoints, cameraMatrix, disCoeffs, rvecCamera2Obj, tvecCamera2Obj);

    //计算重投影误差
    caculateError();

    //单目测距
    distanceSolver(demo);

    //解算欧拉角
    eulerSolver(demo);
}

void Ranger::setCameraMatrix(Mat CM) {
    cameraMatrix = move(CM);
}

void Ranger::setDisCoeffs(Mat DC) {
    disCoeffs = move(DC);
}

