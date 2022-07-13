//
// Created by wjy on 22-7-10.
//
#include "recognize_pkg/System.h"
#include "recognize_pkg/PreProcess.h"
#include "recognize_pkg/Ranger.h"
#include "recognize_pkg/DataReader.h"
#include "iostream"
#include "chrono"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

System *System::pThis = nullptr;

float System::FPS = 0;

bool System::DataRead() {
    DataReader dataReader("/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/CameraDatas.xml");
    if (!dataReader.readData(pThis->cameraMatrix, pThis->disCoeffs)) {
        cout << "Data file root wrong!" << endl;
        return false;
    } else {
        return true;
    }
}

void System::Start(Mat demo) {
    auto start = chrono::system_clock::now();
    //�п��Լ��ж�����
    if (demo.empty()) {
        cout << "Picture read failed" << endl;
        return;
    }
    //������ݶ�ȡ
    Mat mask = demo.clone();
    //Ԥ����(����һ����ֵ��ͼ)
    Mat frame = PreProcess::start(pThis->color,pThis->cameraMatrix,pThis->disCoeffs, mask).clone();
    //���������Լ�ɸѡ
    pThis->ContoursFind(frame);
    //Ѱ��ƥ��ľ���
    pThis->RectFit(demo);
    if (pThis->center.x != 0 && pThis->center.y != 0) {
        //��Ŀ���
        Ranger check;
        check.start(pThis->matchA, pThis->matchB, demo);
    }
    //��������
    //(��������ʵ��)
    //���ݹ���
    pThis->center.x = pThis->center.y = 0;
    cout << "------------------------------------------------" << endl;
    //֡�ʼ���
    auto end = chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    FPS = (double)(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    double s = 1.0 / FPS;
    putText(demo, to_string(s).substr(0, 4),Point(10,50),FONT_HERSHEY_SIMPLEX,1,Scalar(255,0,0),2);
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
    while (true) {
        auto start = chrono::system_clock::now();
        capture >> pThis->demo;
        //�п��Լ��ж�����
        if (pThis->demo.empty()) {
            cout << "Picture read failed" << endl;
            return;
        }
        Mat mask = pThis->demo.clone();
        //Ԥ����(����һ����ֵ��ͼ)
        Mat frame = PreProcess::start(pThis->color, pThis->cameraMatrix, pThis->disCoeffs, mask).clone();
        //���������Լ�ɸѡ
        pThis->ContoursFind(frame);
        //Ѱ��ƥ��ľ���
        pThis->RectFit(pThis->demo);
        if (pThis->center.x != 0 && pThis->center.y != 0) {
            //��Ŀ���
            Ranger check;
            check.start(pThis->matchA, pThis->matchB, pThis->demo);
        }
        //���ݹ���
        pThis->center.x = pThis->center.y = 0;
        cout << "------------------------------------------------" << endl;
        //֡�ʼ���
        auto end = chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        FPS = (double)(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
        double s = 1.0 / FPS;
        putText(pThis->demo, to_string(s).substr(0, 4),Point(10,50),FONT_HERSHEY_SIMPLEX,1,Scalar(255,0,0),2);
        //ͼƬ��ʾ
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

void System::ContoursFind(const Mat &frame) {             /*�������*/
    allContours.clear();
    selectedContours.clear();
    Mat edge = frame.clone();
    findContours(edge, allContours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    for (int i = 0; i < allContours.size(); i++) {
        //���������������븱������ɸѡ����
        if (hierarchy[i][2] == -1 && hierarchy[i][3] == -1) {
            selectedContours.push_back(allContours[i]);
        }
    }
}

/*ѡ���������Ż�,Ŀǰ��ʶ����Ȼ����*/
void System::RectFit(Mat& demo) {
    allRects.clear();
    //ʹ����Բ���
    for (auto &contour: selectedContours) {
        //����̫С�����
        if (contour.size() > 20) {
            allRects.push_back(fitEllipse(contour));
        }
    }
    //�������еľ���(Debug��)
//    for (auto & allRect : allRects) {
//        Point2f point_i[4];
//        allRect.points(point_i);
//        for (int l = 0; l < 4; l++) {
//            line(demo, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 2);
//        }
//    }
    for (int i = 0; i < allRects.size(); i++) {
        //�Ƕȵ���
        float angleI;
        if (allRects[i].angle > 90) {
            angleI = -allRects[i].angle + 90;
        } else {
            angleI = allRects[i].angle;
        }
        for (int j = i + 1; j < allRects.size(); j++) {
            //�Ƕȵ���
            float angleJ;
            if (allRects[j].angle > 90) {
                angleJ = -allRects[j].angle + 90;
            } else {
                angleJ = allRects[j].angle;
            }
            /*************************ʩ������****************************/
            //�Ծ��γ���Ƚ���ɸѡ(���������Ҳ������ҪӰ��)
            if (allRects[i].size.height / allRects[i].size.width >= 5
                && allRects[i].size.height / allRects[i].size.width <= 10
                && allRects[j].size.height / allRects[j].size.width >= 5
                && allRects[j].size.height / allRects[j].size.width <= 10)
                //���������εĽǶȽ���ɸѡ (���Ǵ���б�Ƕ���һ��Լ��?)
                if (angleI * angleJ > 0 && abs(abs(angleI) - abs(angleJ)) < 5)
//                    && (angleI > -50 && angleI < 50) && (angleJ > -50 && angleJ < 50))
                    //���������ε�����������
                    if ((allRects[i].size.area() / allRects[j].size.area() >= 0.5
                        || allRects[j].size.area() / allRects[i].size.area() >= 0.5
                        && (allRects[i].size.area() / allRects[j].size.area() <= 2
                        || allRects[j].size.area() / allRects[i].size.area() <= 2)))
                        //�������ε����ĵ�߶�֮��ܴ�
                        if (abs(allRects[i].center.y - allRects[j].center.y) <=
                            (allRects[i].size.height + allRects[j].size.height) / 8) {
                            /*************************ʩ������****************************/
                            Point2f point_i[4], point_j[4];
                            //�õ��������εĽǵ�
                            allRects[i].points(point_i);
                            allRects[j].points(point_j);
                            //�淶�������ε����λ���Ա��������
                            if (allRects[i].center.x > allRects[j].center.x) {
                                //��ֵ����Ա������������
                                matchA = allRects[j];
                                matchB = allRects[i];
                            } else {
                                matchA = allRects[i];
                                matchB = allRects[j];
                            }
                            center = Point((matchA.center.x + matchB.center.x) / 2,
                                           (matchB.center.y + matchA.center.y) / 2);
                            //����ƥ���ϵľ���
                            for (int l = 0; l < 4; l++) {
                                line(demo, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 2);
                                line(demo, point_j[l], point_j[(l + 1) % 4], Scalar(0, 255, 255), 2);
                            }
                            //����װ�װ�����
                            circle(demo, center, 4, Scalar(0, 255, 255), -1);
                        }
        }
    }
}
