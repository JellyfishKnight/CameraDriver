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
    //�п��Լ��ж�����
    if (demo.empty()) {
        cout << "Picture read failed" << endl;
        return;
    }
    //������ݶ�ȡ
    Mat cameraMatrix, disCoeffs, mask = demo.clone();
    /**·�����ݸ�������޸�**/
    DataReader dataReader("/home/wjy/Projects/RMlearning/CameraDriverWS/src/recognize_pkg/data/data.xml");
    if (dataReader.readData(cameraMatrix, disCoeffs)) {
        undistort(demo, mask, cameraMatrix, disCoeffs);
    } else {
        return ;
    }
    //Ԥ����(����һ����ֵ��ͼ)
    /**�˴�SF**/
    Mat frame = PreProcess::start(pThis->color, mask).clone();
    //���������Լ�ɸѡ
    pThis->ContoursFind(frame);
    //Ѱ��ƥ��ľ���
    pThis->RectFit(mask);
    if (pThis->center.x != 0 && pThis->center.y != 0) {
        //��Ŀ���
        Ranging check;
        check.start(pThis->matchA, pThis->matchB, mask);
    }
    //��������
    //���ݹ���
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
        //�п��Լ��ж�����
        if (pThis->demo.empty()) {
            cout << "Picture read failed" << endl;
            return;
        }
        //������ݶ�ȡ
        Mat cameraMatrix, disCoeffs, mask = pThis->demo.clone();
        /**·�����ݸ�������޸�**/
        DataReader dataReader("/home/wjy/Projects/RMlearning/CameraDriverWS/src/recognize_pkg/data/data.xml");
        if (dataReader.readData(cameraMatrix, disCoeffs)) {
            undistort(pThis->demo, mask, cameraMatrix, disCoeffs);
        } else {
            return;
        }
        //Ԥ����(����һ����ֵ��ͼ)
        Mat frame = PreProcess::start(pThis->color, mask).clone();
        //���������Լ�ɸѡ
        pThis->ContoursFind(frame);
        //Ѱ��ƥ��ľ���
        pThis->RectFit(pThis->demo);
        if (pThis->center.x != 0 && pThis->center.y != 0) {
            //��Ŀ���
            Ranging check;
            check.start(pThis->matchA, pThis->matchB, pThis->demo);
        }
        //���ݹ���
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
void System::RectFit(Mat &mask) {
    allRects.clear();
    //ʹ����Բ���
    for (auto &contour: selectedContours) {
        //����̫С�����
        if (contour.size() > 20) {
            allRects.push_back(fitEllipse(contour));
        }
    }
    for (int i = 0; i < allRects.size(); i++) {
        for (int j = i + 1; j < allRects.size(); j++) {
            float angleI, angleJ;
            //�Ƕȵ���
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
            //�Ծ��γ���Ƚ���ɸѡ
            if (allRects[i].size.height / allRects[i].size.width >= 2
                && allRects[i].size.height / allRects[i].size.width <= 7
                && allRects[j].size.height / allRects[j].size.width >= 2
                && allRects[j].size.height / allRects[j].size.width <= 7)
                //���������εĽǶȽ���ɸѡ
                if (angleI * angleJ > 0 && abs(abs(angleI) - abs(angleJ)) < 5)
//                    && (angleI > -50 && angleI < 50) && (angleJ > -50 && angleJ < 50))
                    //���������ε�����������
                    if ((allRects[i].size.area() / allRects[j].size.area() >= 0.9
                        || allRects[j].size.area() / allRects[i].size.area() >= 0.9
                        && (allRects[i].size.area() / allRects[j].size.area() <= 1.11
                        || allRects[j].size.area() / allRects[i].size.area() <= 1.11)))
                        //�������ε����ĵ�߶�֮��ܴ�
                        if (abs(allRects[i].center.y - allRects[j].center.y) <=
                            (allRects[i].size.height + allRects[j].size.height) / 8) {
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
                                line(pThis->demo, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 2);
                                line(pThis->demo, point_j[l], point_j[(l + 1) % 4], Scalar(0, 255, 255), 2);
                            }
                            //����װ�װ�����
                            circle(pThis->demo, center, 4, Scalar(0, 255, 255), -1);
                        }
        }
    }
}
