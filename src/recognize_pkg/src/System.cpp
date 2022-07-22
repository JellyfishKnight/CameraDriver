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


void System::ContoursFind(const Mat &frame) {             /*�������*/
    allContours.clear();
    selectedContours.clear();
    Mat edge = frame.clone();
    findContours(edge, allContours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    for (int i = 0; i < allContours.size(); i++) {
        if (allContours[i].size() > 20)
            selectedContours.push_back(allContours[i]);
        //���������������븱������ɸѡ����(����ʵ������м���û�й��ص�����,��ֻѰ���ⲿ����)
//        if (hierarchy[i][2] != -1 && hierarchy[i][3] == -1) {
//        }
    }
}

/*ѡ���������Ż�,Ŀǰ��ʶ����Ȼ����*/
void System::RectFit(Mat &src) {
    allRects.clear();
    //ʹ����Բ���
    for (auto &contour: selectedContours) {
        //����̫С�����
        if (contour.size() > 20) {
            allRects.push_back(fitEllipse(contour));
        }
    }
//    //�������еľ���(Debug��)
//    for (auto & allRect : allRects) {
//        Point2f point_i[4];
//        allRect.points(point_i);
//        for (int l = 0; l < 4; l++) {
//            line(demo, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 2);
//        }
//    }
    for (int i = 0; i < allRects.size(); i++) {
        //�Ƕȵ���
        angleI = adjustAngle(allRects[i]);
        for (int j = i + 1; j < allRects.size(); j++) {
            //�Ƕȵ���
            angleJ = adjustAngle(allRects[j]);
            if (selectionOfRects(allRects[i], allRects[j])) {
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
                    line(src, point_i[l], point_i[(l + 1) % 4], Scalar(0, 255, 255), 2);
                    line(src, point_j[l], point_j[(l + 1) % 4], Scalar(0, 255, 255), 2);
                }
                //����װ�װ�����
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
    //�Ե���I�ĵ���ɸѡ
    //�Ե����Ƕ�ɸѡ
    if (abs(angleI) <= 80 && abs(angleI) >= 10)
        return false;
    //�Ծ��γ���Ƚ���ɸѡ
    if (a.size.height / a.size.width >= maxLenRatio
        && a.size.height / a.size.width <= minLenRatio)
        return false;
    //�Ե���J�ĵ���ɸѡ
    //�Ե����Ƕ�ɸѡ
    if (abs(angleJ) <= 80 && abs(angleJ) >= 10)
        return false;
    //�Ծ��γ���Ƚ���ɸѡ(���������Ҳ������ҪӰ��)
    if (b.size.height / b.size.width >= maxLenRatio
        && b.size.height / b.size.width <= minLenRatio)
        return false;
    //���������������ɸѡ
    //��������������б�ǶȽ���ɸѡ
    //�Ծ��εĽǶȽ���ɸѡ
    if (angleI * angleJ <= 0)
        return false;
    if (abs(abs(angleI) - abs(angleJ)) > maxAngleError)
        return false;
    //�������ε����ĵ�߶�֮��ܴ�
    if (abs(a.center.y - b.center.y) >=
        (a.size.height + b.size.height) / 8)
        return false;
    //���������ε�����Ƚ���ɸѡ
    if (a.size.area() / b.size.area() >= maxAreaRation
        || b.size.area() / a.size.area() >= maxAreaRation)
        return false;
//            //��ѡ���ľ��εĳ���Ƚ���ɸѡ
//            float imageWidth = abs(sqrt(pow(allRects[i].center.x - allRects[j].center.y, 2) + pow(allRects[i].center.y - allRects[j].center.y, 2)));
//            float imageHeight = (allRects[i].size.height + allRects[j].size.height) / 2;
//            if (imageHeight / imageWidth < minImageRatio && imageHeight / imageWidth > maxImageRatio)
//                return false;
    return true;
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
    Mat frame = PreProcess::start(pThis->color, pThis->cameraMatrix, pThis->disCoeffs, mask).clone();

    //���������Լ�ɸѡ
    pThis->ContoursFind(frame);

    //Ѱ��ƥ��ľ���
    pThis->RectFit(demo);

    if (pThis->center.x != 0 && pThis->center.y != 0) {
        //��Ŀ���
        Ranger ranger(pThis->cameraMatrix, pThis->disCoeffs);
        ranger.start(pThis->matchA, pThis->matchB, demo);
        //��ȡ������װ�װ�ROI���������ʶ��ģ��
    }

    //���ݹ���
    pThis->center.x = pThis->center.y = 0;
    cout << "------------------------------------------------" << endl;

    //֡�ʼ���
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
            Ranger check(pThis->cameraMatrix, pThis->disCoeffs);
            check.start(pThis->matchA, pThis->matchB, pThis->demo);
            //��ȡ������װ�װ�ROI���������ʶ��ģ��
            Ranger::setBoardSize(pThis->number.start(check.getROI(forNumber)));

        }

        //���ݹ���
        pThis->center.x = pThis->center.y = 0;
        cout << "------------------------------------------------" << endl;

        //֡�ʼ���
        auto end = chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        FPS = (double) (duration.count()) * std::chrono::microseconds::period::num /
              std::chrono::microseconds::period::den;
        double s = 1.0 / FPS;
        putText(pThis->demo, to_string(s).substr(0, 4), Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);

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
