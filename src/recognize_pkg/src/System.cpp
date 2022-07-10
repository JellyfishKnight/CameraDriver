//
// Created by wjy on 22-7-10.
//
#include "recognize_pkg/System.h"
#include "recognize_pkg/PreProcess.h"
#include "recognize_pkg/Ranger.h"
#include "iostream"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

System *System::pThis = nullptr;

void System::Start(Mat demo) {
//        VideoCapture capture(pThis->root);
//        if (!capture.isOpened()) {
//            cout << "Filename is wrong!" << endl;
//            return;
//        }
//        while (true) {
//            capture >> demo;
//            //�п��Լ��ж�����
//            if (demo.empty()) {
//                cout << "Picture read failed" << endl;
//                return;
//            }
//            //Ԥ����(����һ����ֵ��ͼ)
//            Mat frame = PreProcess::start(pThis->color, demo).clone();
//            //���������Լ�ɸѡ
//            pThis->ContoursFind(frame);
//            //Ѱ��ƥ��ľ���
//            pThis->RectFit(demo);
//            if (pThis->center.x != 0 && pThis->center.y != 0) {
//                //��Ŀ���
//                Ranging check;
//                check.start(pThis->matchA, pThis->matchB, demo);
//            }
//            //���ݹ���
//            pThis->center.x = pThis->center.y = 0;
//            cout << "------------------------------------------------" << endl;
//            namedWindow("demo", WINDOW_NORMAL);
//            imshow("demo", demo);
//            int control = waitKey(1);
//            if (control == 27) {
//                break;
//            }
//        }
    //�п��Լ��ж�����
    if (demo.empty()) {
        cout << "Picture read failed" << endl;
        return;
    }
    //Ԥ����(����һ����ֵ��ͼ)
    Mat frame = PreProcess::start(pThis->color, demo).clone();
    //���������Լ�ɸѡ
    pThis->ContoursFind(frame);
    //Ѱ��ƥ��ľ���
    pThis->RectFit(demo);
    if (pThis->center.x != 0 && pThis->center.y != 0) {
        //��Ŀ���
        Ranging check;
        check.start(pThis->matchA, pThis->matchB, demo);
    }
    //���ݹ���
    pThis->center.x = pThis->center.y = 0;
    cout << "------------------------------------------------" << endl;
    namedWindow("demo", WINDOW_NORMAL);
    imshow("demo", demo);
    waitKey(1);
}

void System::ContoursFind(const Mat &frame) {
    allContours.clear();
    selectedContours.clear();
    Mat edge = frame.clone();
    findContours(edge, allContours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    for (int i = 0; i < allContours.size(); i++) {
        //���������������븱������ɸѡ����
        if (hierarchy[i][2] == -1 && hierarchy[i][3] != -1) {
            selectedContours.push_back(allContours[i]);
        }
    }
}

/*ѡ���������Ż�,Ŀǰ��ʶ����Ȼ����*/
void System::RectFit(Mat &demo) {
    allRects.clear();
    //ʹ����Բ���
    for (auto &contour: selectedContours) {
        if (contour.size() > 100 && contour.size() < 800) {
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
                    //���������ε�����������
                    if ((allRects[i].size.area() / allRects[j].size.area() >= 0.8
                         || allRects[j].size.area() / allRects[i].size.area() >= 0.8
                            && (allRects[i].size.area() / allRects[j].size.area() <= 1.25
                                || allRects[j].size.area() / allRects[i].size.area() <= 1.25)))
                        //�������ε����ĵ�߶�֮��ܴ�
                        if (abs(allRects[i].center.y - allRects[j].center.y) <=
                            (allRects[i].size.height + allRects[j].size.height) / 4) {
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
                                line(demo, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 10);
                                line(demo, point_j[l], point_j[(l + 1) % 4], Scalar(0, 255, 255), 10);
                            }
                            //����װ�װ�����
                            circle(demo, center, 10, Scalar(0, 255, 255), -1);
                        }
        }
    }
}
