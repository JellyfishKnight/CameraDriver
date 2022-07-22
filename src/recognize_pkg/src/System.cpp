//
// Created by wjy on 22-7-10.
//
#include "recognize_pkg/System.h"
#include "recognize_pkg/PreProcess.h"
#include "recognize_pkg/Ranger.h"
#include "recognize_pkg/DataReader.h"
#include "iostream"
#include "string"
#include "chrono"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"



using namespace std;
using namespace cv;

System *System::pThis = nullptr;

float System::FPS = 0;

bool System::DataRead() {
    DataReader dataReader(pThis->dataRoot);
    if (!dataReader.readData(pThis->cameraMatrix, pThis->disCoeffs)) {
        cout << "Data file root wrong!" << endl;
        return false;
    } else {
        return true;
    }
}


void System::ContoursFind(const Mat &frame) {             /*调试完毕*/
    allContours.clear();
    selectedContours.clear();
    Mat edge = frame.clone();
    findContours(edge, allContours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (int i = 0; i < allContours.size(); i++) {
        if (allContours[i].size() > 20)
            selectedContours.push_back(allContours[i]);
        //根据有无子轮廓与副轮廓来筛选轮廓(根据实际情况中几乎没有过曝的现象,将只寻找外部轮廓)
//        if (hierarchy[i][2] != -1 && hierarchy[i][3] == -1) {
//        }
    }
}

/*选择条件待优化,目前误识别依然存在*/
void System::RectFit(Mat &src) {
    allRects.clear();
    //使用椭圆拟合
    for (auto &contour: selectedContours) {
        //过滤太小的噪点
        if (contour.size() > 20) {
            allRects.push_back(fitEllipse(contour));
        }
    }
//    //画出所有的矩形(Debug用)
//    for (auto & allRect : allRects) {
//        Point2f point_i[4];
//        allRect.points(point_i);
//        for (int l = 0; l < 4; l++) {
//            line(demo, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 2);
//        }
//    }
    for (int i = 0; i < allRects.size(); i++) {
        //角度调整
        angleI = adjustAngle(allRects[i]);
        for (int j = i + 1; j < allRects.size(); j++) {
            //角度调整
            angleJ = adjustAngle(allRects[j]);
            if (selectionOfRects(allRects[i], allRects[j])) {
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
                    line(src, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 2);
                    line(src, point_j[l], point_j[(l + 1) % 4], Scalar(0, 255, 255), 2);
                }
                //画出装甲板中心
                circle(src, center, 4, Scalar(0, 255, 255), -1);
            }
        }
    }
}

float System::adjustAngle(const RotatedRect &a) {
    float adjustedAngle;
    if (a.angle > 90) {
        adjustedAngle = -a.angle + 90;
    } else {
        adjustedAngle = a.angle;
    }
    return adjustedAngle;
}

bool System::selectionOfRects(const RotatedRect &a, const RotatedRect &b) {
    //对灯条I的单独筛选
    //对灯条角度筛选
    if (abs(angleI) <= 80 && abs(angleI) >= 10)
        return false;
    //对矩形长宽比进行筛选
    if (a.size.height / a.size.width >= maxLenRatio
        && a.size.height / a.size.width <= minLenRatio)
        return false;
    //对灯条J的单独筛选
    //对灯条角度筛选
    if (abs(angleJ) <= 80 && abs(angleJ) >= 10)
        return false;
    //对矩形长宽比进行筛选(灯条长宽比也许是主要影响)
    if (b.size.height / b.size.width >= maxLenRatio
        && b.size.height / b.size.width <= minLenRatio)
        return false;
    //对两个灯条的配对筛选
    //对两个灯条的倾斜角度进行筛选
    //对矩形的角度进行筛选
    if (angleI * angleJ <= 0)
        return false;
    if (abs(abs(angleI) - abs(angleJ)) > maxAngleError)
        return false;
    //两个矩形的中心点高度之差不能大
    if (abs(a.center.y - b.center.y) >=
        (a.size.height + b.size.height) / 8)
        return false;
    //对两个矩形的面积比进行筛选
    if (a.size.area() / b.size.area() >= maxAreaRation
        || b.size.area() / a.size.area() >= maxAreaRation)
        return false;
//            //对选出的矩形的长宽比进行筛选
//            float imageWidth = abs(sqrt(pow(allRects[i].center.x - allRects[j].center.y, 2) + pow(allRects[i].center.y - allRects[j].center.y, 2)));
//            float imageHeight = (allRects[i].size.height + allRects[j].size.height) / 2;
//            if (imageHeight / imageWidth < minImageRatio && imageHeight / imageWidth > maxImageRatio)
//                return false;
    return true;
}


void System::Start(Mat demo) {
    auto start = chrono::system_clock::now();
    //判空以及判定结束
    if (demo.empty()) {
        cout << "Picture read failed" << endl;
        return;
    }
    //相机数据读取
    Mat mask = demo.clone();

    //预处理(返回一个二值化图)
    Mat frame = PreProcess::start(pThis->color, pThis->cameraMatrix, pThis->disCoeffs, mask).clone();

    //轮廓查找以及筛选
    pThis->ContoursFind(frame);

    //寻找匹配的矩形
    pThis->RectFit(demo);

    if (pThis->center.x != 0 && pThis->center.y != 0) {
        //单目测距
        Ranger ranger(pThis->cameraMatrix, pThis->disCoeffs);
        ranger.start(pThis->matchA, pThis->matchB, demo);
        //获取并发送装甲板ROI区域给数字识别模块
    }

    //数据归零
    pThis->center.x = pThis->center.y = 0;
    cout << "------------------------------------------------" << endl;

    //帧率计算
    auto end = chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    FPS = (double) (duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    double s = 1.0 / FPS;
    putText(demo, to_string(s).substr(0, 4), Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
    namedWindow("mask", WINDOW_NORMAL);
    imshow("mask", demo);
    waitKey(1);
}


void System::Start() {
    VideoCapture capture(pThis->root);
    if (!capture.isOpened()) {
        cout << "Filename is wrong!" << endl;
        return;
    }
    cout << "Started!" << endl;
    Mat forNumber;
    while (true) {
        auto start = chrono::system_clock::now();
        capture >> pThis->demo;

        forNumber = pThis->demo.clone();

        //判空以及判定结束
        if (pThis->demo.empty()) {
            cout << "Picture read failed" << endl;
            return;
        }
        Mat mask = pThis->demo.clone();

        //预处理(返回一个二值化图)
        Mat frame = PreProcess::start(pThis->color, pThis->cameraMatrix, pThis->disCoeffs, mask).clone();

        //轮廓查找以及筛选
        pThis->ContoursFind(frame);

        //寻找匹配的矩形
        pThis->RectFit(pThis->demo);

        if (pThis->center.x != 0 && pThis->center.y != 0) {
            //单目测距
            Ranger check(pThis->cameraMatrix, pThis->disCoeffs);
            check.start(pThis->matchA, pThis->matchB, pThis->demo);
            //获取并发送装甲板ROI区域给数字识别模块
            Ranger::setBoardSize(pThis->number.start(check.getROI(forNumber)));

        }

        //数据归零
        pThis->center.x = pThis->center.y = 0;
        cout << "------------------------------------------------" << endl;

        //帧率计算
        auto end = chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        FPS = (double) (duration.count()) * std::chrono::microseconds::period::num /
              std::chrono::microseconds::period::den;
        double s = 1.0 / FPS;
        putText(pThis->demo, to_string(s).substr(0, 4), Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);

        //图片显示
        namedWindow("demo", WINDOW_NORMAL);
        imshow("demo", pThis->demo);
        if (waitKey(1) == 27) {
            break;
        }
    }
    capture.release();
    cout << "Finished!" << endl;
    waitKey(0);
}
