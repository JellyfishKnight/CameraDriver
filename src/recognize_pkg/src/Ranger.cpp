//
// Created by wjy on 22-7-10.
//

#include <iostream>
#include "recognize_pkg/Ranger.h"
#include "Eigen/Eigen"
#include "opencv2/core/eigen.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"

using namespace std;
using namespace cv;


void Ranging::init(const RotatedRect& a, const RotatedRect& b) {            /*�������*/
    //�궨�����ݶ�ȡ
    cameraMatrix = (Mat_<float>(3, 3) << 1344.386380273769, 0, 648.6569061023351,
            0, 1344.404855884417, 475.3889678346135,
            0, 0, 1);
    disCoeffs = (Mat_<float>(1, 5) << -0.06550846603470172, 0.06305921474841766, 9.789393321568021e-05,
            0.001037227953363168, 0.411048839130545);
    Point2f pointA[4], pointB[4];
    a.points(pointA);
    b.points(pointB);
    points = new Point2f[9];
    Point2f center((a.center.x + b.center.x) / 2.0, (a.center.y + b.center.y) / 2.0);
    points[0] = center;                                                  //��֤���ݵĶ���
    if (a.angle > 90) {
        points[1] = pointA[3];
        points[2] = pointA[0];
        points[3] = pointB[3];
        points[4] = pointB[0];
        points[5] = pointB[1];
        points[6] = pointB[2];
        points[7] = pointA[1];
        points[8] = pointA[2];
    } else {
        points[1] = pointA[1];
        points[2] = pointA[2];
        points[3] = pointB[1];
        points[4] = pointB[2];
        points[5] = pointB[3];
        points[6] = pointB[0];
        points[7] = pointA[3];
        points[8] = pointA[0];
    }
//    Mat test = Mat::zeros(Size(2000,2000), CV_8UC1);
//    for (int i = 0; i < 9; i++) {
//        putText(test, to_string(i), points[i], FONT_HERSHEY_SIMPLEX, 2,Scalar(255,255,255), 2);
//    }
//    namedWindow("test", WINDOW_NORMAL);
//    imshow("test", test);
}

vector<Point3f> Ranging::getObjPoints() {                                   /*�������*/
    float maxRight = 0, minLeft = INFINITY, maxDown = 0, minUp = INFINITY;
    //�淶�߽�,��ֹ��ֵԽ��
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
    float imageWidth = maxRight - minLeft;
    float imageHeight = maxDown - minUp;
    vector<Point3f> objPoints;
    Point3f temp(0, 0, 0);
//    temp.x = abs((points[0].x - points[1].x) / imageWidth * boardWidth);
//    temp.y = abs((points[0].y - points[1].y) / imageHeight * boardHeight);
    objPoints.push_back(temp);
    for (int i = 1; i < 9; i++) {
        temp.x = (points[i].x - points[0].x) / imageWidth * boardWidth;
        temp.y = (points[i].y - points[0].y) / imageHeight * boardHeight;
        objPoints.push_back(temp);
    }
    return objPoints;
}



void Ranging::caculateError(Mat& rvec, Mat& tvec) {                         /*�������*/
    vector<Point3f> objPoints = getObjPoints();
    vector<Point2f> outPutPoints;                       //3d��2d��ͶӰ
    projectPoints(objPoints, rvec, tvec , cameraMatrix, disCoeffs, outPutPoints);
    Mat test = Mat::zeros(Size(2000,2000), CV_8UC1);
//    for (int i = 0; i < outPutPoints.size(); i++) {
//        putText(test, to_string(i), outPutPoints[i], FONT_HERSHEY_SIMPLEX, 2, Scalar(255,255,255),2);
//    }
//    namedWindow("test", WINDOW_NORMAL);
//    imshow("test", test);
    float totalError = 0;
    for (int i = 0; i < outPutPoints.size(); i++) {
        totalError += sqrt(pow((points[i].x - outPutPoints[i].x), 2) + pow((points[i].y - outPutPoints[i].y), 2));
    }
    totalError /= 9;
    cout << "Average error is : " << totalError << endl;
}

void Ranging::start(const RotatedRect& a, const RotatedRect& b, Mat& demo) {        /**�����̬�����Լ��������������**/
    //��ʼ��
    init(a, b);

    //��ȡ��������ϵ��
    vector<Point3f> objPoints = getObjPoints();
    vector<Point2f> imgPoints(points, points + 9);

    //solvePnP���ص���ת������ƽ������
    Mat rvecCamera2Obj, tvecCamera2Obj;
    solvePnP(objPoints, imgPoints, cameraMatrix, disCoeffs, rvecCamera2Obj, tvecCamera2Obj);

    //������ͶӰ���
    caculateError(rvecCamera2Obj, tvecCamera2Obj);

    Mat rotRvec;                                                    //����ת����ת��Ϊ
    Rodrigues(rvecCamera2Obj, rotRvec);                     //��ת����
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> RMatrix;   //��opencv����ת��ΪEigen�ľ���,�����������
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> TMatrix;
    cv2eigen(rotRvec, RMatrix);
    cv2eigen(tvecCamera2Obj, TMatrix);
    Eigen::Vector3f cameraPoint;
    //����������������ϵ�е�����
    cameraPoint = -RMatrix.inverse() * TMatrix;
    //��������װ�װ����ĵľ���
    /**�ⲿ����ĳЩʱ�������Ȼ��׼ȷ,����Ӧ�ò����㷨�ϵ�����,Ŀǰ����������Ƶ���ʷ��������**/
    float tx, ty, tz;
    tx = tvecCamera2Obj.at<double>(0);
    ty = tvecCamera2Obj.at<double>(1);
    tz = tvecCamera2Obj.at<double>(2);
    float distObj2Camera = sqrt(tx * tx + ty * ty + tz * tz);
    //��ͼ�ϱ��װ�װ�ľ���
    putText(demo,"Dist:" + to_string(distObj2Camera).substr(0, 6), points[4], FONT_HERSHEY_SIMPLEX,0.5, Scalar(0,255,0),2);


    float thetaY, thetaX, thetaZ;
    //������ת�������������ת��
    thetaX = atan2(rotRvec.at<double>(2,1), rotRvec.at<double>(2,2));
    thetaY = atan2(-rotRvec.at<double>(2,0), sqrt(rotRvec.at<double>(2,1) * rotRvec.at<double>(2,1) + rotRvec.at<double>(2,2) * rotRvec.at<double>(2,2)));
    thetaZ = atan2 (rotRvec.at<double>(1, 0), rotRvec.at<double>(0, 0));
    //    yaw = atan2(rotRvec.at<double>(0, 2), rotRvec.at<double>(2, 2));
//    pitch = asin(-rotRvec.at<double>(1, 2));
    thetaY = thetaY * 180.0 / CV_PI;                                       //�ӻ���ת��Ϊ�Ƕ�
    thetaX = thetaX * 180.0 / CV_PI;
    thetaZ = thetaZ * 180.0 / CV_PI;
//    cout << rotRvec << endl;
    putText(demo, "Y" + to_string(thetaY).substr(0, 4), points[1], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0,255), 2);
    putText(demo, "X:" + to_string(thetaX).substr(0, 4), points[8], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 2);
    putText(demo, "Z:" + to_string(thetaZ).substr(0, 4), points[5], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 2);
}