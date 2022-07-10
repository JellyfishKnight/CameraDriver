//
// Created by wjy on 22-7-10.
//
#include "recognize_pkg/System.h"
#include "recognize_pkg/PreProcess.h"
#include "recognize_pkg/Ranger.h"
#include "recognize_pkg/DataReader.h"
#include "iostream"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;


System *System::pThis = nullptr;

void System::Start(Mat demo) {
    //判空以及判定结束
    if (demo.empty()) {
        cout << "Picture read failed" << endl;
        return;
    }
    //相机数据读取
    Mat cameraMatrix, disCoeffs, mask = demo.clone();
    /**路径根据个人情况修改**/
    DataReader dataReader("/home/wjy/Projects/RMlearning/CameraDriverWS/src/recognize_pkg/data/data.xml");
    if (dataReader.readData(cameraMatrix, disCoeffs)) {
        undistort(demo, mask, cameraMatrix, disCoeffs);
    } else {
        return ;
    }
    //预处理(返回一个二值化图)
    /**此处SF**/
    Mat frame = PreProcess::start(pThis->color, mask).clone();
    //轮廓查找以及筛选
    pThis->ContoursFind(frame);
    //寻找匹配的矩形
    pThis->RectFit(mask);
    if (pThis->center.x != 0 && pThis->center.y != 0) {
        //单目测距
        Ranging check;
        check.start(pThis->matchA, pThis->matchB, mask);
    }
    //查找数字
    //数据归零
    pThis->center.x = pThis->center.y = 0;
    cout << "------------------------------------------------" << endl;
    namedWindow("mask", WINDOW_NORMAL);
    imshow("mask", mask);
    waitKey(1);
}

void System::Start() {
    VideoCapture capture(pThis->root);
    if (!capture.isOpened()) {
        cout << "Filename is wrong!" << endl;
        return;
    }
    cout << "Started!" << endl;
    while (true) {
        capture >> pThis->demo;
        //判空以及判定结束
        if (pThis->demo.empty()) {
            cout << "Picture read failed" << endl;
            return;
        }
        //相机数据读取
        Mat cameraMatrix, disCoeffs, mask = pThis->demo.clone();
        /**路径根据个人情况修改**/
        DataReader dataReader("/home/wjy/Projects/RMlearning/CameraDriverWS/src/recognize_pkg/data/data.xml");
        if (dataReader.readData(cameraMatrix, disCoeffs)) {
            undistort(pThis->demo, mask, cameraMatrix, disCoeffs);
        } else {
            return;
        }
        //预处理(返回一个二值化图)
        Mat frame = PreProcess::start(pThis->color, mask).clone();
        //轮廓查找以及筛选
        pThis->ContoursFind(frame);
        //寻找匹配的矩形
        pThis->RectFit(pThis->demo);
        if (pThis->center.x != 0 && pThis->center.y != 0) {
            //单目测距
            Ranging check;
            check.start(pThis->matchA, pThis->matchB, pThis->demo);
        }
        //数据归零
        pThis->center.x = pThis->center.y = 0;
        cout << "------------------------------------------------" << endl;
        namedWindow("demo", WINDOW_NORMAL);
        imshow("demo", pThis->demo);
        if (waitKey(1) == 27) {
            break;
        }
    }
    cout << "Finished!" << endl;
    waitKey(0);
}

void System::ContoursFind(const Mat &frame) {             /*调试完毕*/
    allContours.clear();
    selectedContours.clear();
    Mat edge = frame.clone();
    findContours(edge, allContours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    for (int i = 0; i < allContours.size(); i++) {
        //根据有无子轮廓与副轮廓来筛选轮廓
        if (hierarchy[i][2] == -1 && hierarchy[i][3] == -1) {
            selectedContours.push_back(allContours[i]);
        }
    }
}

/*选择条件待优化,目前误识别依然存在*/
void System::RectFit(Mat &mask) {
    allRects.clear();
    //使用椭圆拟合
    for (auto &contour: selectedContours) {
        //过滤太小的噪点
        if (contour.size() > 20) {
            allRects.push_back(fitEllipse(contour));
        }
    }
    for (int i = 0; i < allRects.size(); i++) {
        for (int j = i + 1; j < allRects.size(); j++) {
            float angleI, angleJ;
            //角度调整
            if (allRects[i].angle > 90) {
                angleI = -allRects[i].angle + 90;
            } else {
                angleI = allRects[i].angle;
            }
            if (allRects[j].angle > 90) {
                angleJ = -allRects[j].angle + 90;
            } else {
                angleJ = allRects[j].angle;
            }
            //对矩形长宽比进行筛选
            if (allRects[i].size.height / allRects[i].size.width >= 2
                && allRects[i].size.height / allRects[i].size.width <= 7
                && allRects[j].size.height / allRects[j].size.width >= 2
                && allRects[j].size.height / allRects[j].size.width <= 7)
                //对两个矩形的角度进行筛选
                if (angleI * angleJ > 0 && abs(abs(angleI) - abs(angleJ)) < 5)
//                    && (angleI > -50 && angleI < 50) && (angleJ > -50 && angleJ < 50))
                    //对两个矩形的面积进行配对
                    if ((allRects[i].size.area() / allRects[j].size.area() >= 0.9
                        || allRects[j].size.area() / allRects[i].size.area() >= 0.9
                        && (allRects[i].size.area() / allRects[j].size.area() <= 1.11
                        || allRects[j].size.area() / allRects[i].size.area() <= 1.11)))
                        //两个矩形的中心点高度之差不能大
                        if (abs(allRects[i].center.y - allRects[j].center.y) <=
                            (allRects[i].size.height + allRects[j].size.height) / 8) {
                            Point2f point_i[4], point_j[4];
                            //得到两个矩形的角点
                            allRects[i].points(point_i);
                            allRects[j].points(point_j);
                            //规范两个矩形的相对位置以便后续解算
                            if (allRects[i].center.x > allRects[j].center.x) {
                                //赋值给成员变量储存起来
                                matchA = allRects[j];
                                matchB = allRects[i];
                            } else {
                                matchA = allRects[i];
                                matchB = allRects[j];
                            }
                            center = Point((matchA.center.x + matchB.center.x) / 2,
                                           (matchB.center.y + matchA.center.y) / 2);
                            //画出匹配上的矩形
                            for (int l = 0; l < 4; l++) {
                                line(pThis->demo, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 2);
                                line(pThis->demo, point_j[l], point_j[(l + 1) % 4], Scalar(0, 255, 255), 2);
                            }
                            //画出装甲板中心
                            circle(pThis->demo, center, 4, Scalar(0, 255, 255), -1);
                        }
        }
    }
}
