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

/*�������*/
void Ranger::init(const RotatedRect& a, const RotatedRect& b) {
    //�궨�����ݶ�ȡ
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
    //��֤���ݵĶ���
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


/*�������*/
vector<Point3f> Ranger::getObjPoints() {
    //�淶�߽�,��ֹ��ֵԽ��
    calculateTheSizeOfImage();
    vector<Point3f> objPoints;
    Point3f temp(0, 0, 0);
    objPoints.push_back(temp);
    //����ÿ��������������ϵ�е�����
    for (int i = 1; i < 9; i++) {
        temp.x = (points[i].x - points[0].x) / imageWidth * boardWidth;
        temp.y = (points[i].y - points[0].y) / imageHeight * boardHeight;
        objPoints.push_back(temp);
    }
    return objPoints;
}

void Ranger::calculateTheSizeOfImage() {
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
    //����ͼ����װ�װ�ĳ���
    imageWidth = maxRight - minLeft;
    imageHeight = maxDown - minUp;
}


/*�������*/
void Ranger::caculateError() {
    vector<Point3f> objPoints = getObjPoints();
    vector<Point2f> outPutPoints;                       //3d��2d��ͶӰ
    projectPoints(objPoints, rvecCamera2Obj, tvecCamera2Obj, cameraMatrix, disCoeffs, outPutPoints);
    Mat test = Mat::zeros(Size(2000,2000), CV_8UC1);
    float totalError = 0;
    for (int i = 0; i < outPutPoints.size(); i++) {
        totalError += sqrt(pow((points[i].x - outPutPoints[i].x), 2) + pow((points[i].y - outPutPoints[i].y), 2));
    }
    totalError /= 9;
    cout << "Average error is : " << totalError << endl;
}

void Ranger::distanceSolver(Mat &demo) {     //����ת����ת��Ϊ
    Mat rotRvec;
    Rodrigues(rvecCamera2Obj, rotRvec);                     //��ת����
    //��opencv����ת��ΪEigen�ľ���,�����������
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> RMatrix;
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> TMatrix;
    cv2eigen(rotRvec, RMatrix);
    cv2eigen(tvecCamera2Obj, TMatrix);
    Eigen::Vector3f cameraPoint;
    //����������������ϵ�е�����
    //cameraPoint = -RMatrix.inverse() * TMatrix;
    //��������װ�װ����ĵľ���
    tx = tvecCamera2Obj.at<double>(0);
    ty = tvecCamera2Obj.at<double>(1);
    tz = tvecCamera2Obj.at<double>(2);
    distObj2Camera = sqrt(tx * tx + ty * ty + tz * tz);
    //��ͼ�ϱ��װ�װ�ľ���
    putText(demo,"Dist:" + to_string(distObj2Camera).substr(0, 6), points[4], FONT_HERSHEY_SIMPLEX,0.5, Scalar(0,255,0),2);
}

void Ranger::eulerSolver(Mat &demo) {
    //������,ˮƽת����
    double pitch, yaw;
    yaw = atan2(tvecCamera2Obj.at<double>(0), tvecCamera2Obj.at<double>(2));
    pitch = -atan2(tvecCamera2Obj.at<double>(1),sqrt(tvecCamera2Obj.at<double>(0) * tvecCamera2Obj.at<double>(0) + tvecCamera2Obj.at<double>(2) * tvecCamera2Obj.at<double>(2)));
    //�ӻ���ת��Ϊ�Ƕ�
    yaw *= 180.0 / CV_PI;
    pitch *= 180.0 / CV_PI;
    cout << "Yaw: " << yaw << endl;
    cout << "Pitch: " << pitch << endl;
    putText(demo, "yaw" + to_string(yaw).substr(0, 4), points[1], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0,255), 2);
    putText(demo, "pitch:" + to_string(pitch).substr(0, 4), points[8], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 2);
}

/**
 * @brief ͨ����������ʶ�������ص����ֹ淶װ�װ�ߴ�
 * @param number װ�װ���
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
    //ָ��ROI������ĸ��ǵ�
    pointsOfROI[0] = Point2f(points[1].x + 10, points[1].y - 10);
    pointsOfROI[1] = Point2f(points[4].x - 10, points[4].y - 10);
    pointsOfROI[2] = Point2f(points[5].x - 10, points[5].y + 10);
    pointsOfROI[3] = Point2f(points[8].x + 10, points[8].y + 10);
    //��֤���ݵĶ���
    pointsOfNumber[0] = Point2f(0, 0);
    pointsOfNumber[1] = Point2f(demo.cols, 0);
    pointsOfNumber[2] = Point2f(demo.cols, demo.rows);
    pointsOfNumber[3] = Point2f(0, demo.rows);
    Mat ROI;
    //��ȡ͸�ӱ任����
    Mat tranMat = getPerspectiveTransform(pointsOfROI, pointsOfNumber);
    warpPerspective(demo, ROI, tranMat, ROI.size());
    //�淶���ݷ��͸�ʽ,ʹ���ܹ���Ԥ��
    resize(ROI, ROI, Size(20, 20));
    return ROI;
}

void Ranger::start(const RotatedRect& a, const RotatedRect& b, Mat& demo) {        /**ʣ��Ľ���ŷ������ʱû�н��**/
    //��ʼ��
    init(a, b);

    //��ȡ��������ϵ��
    vector<Point3f> objPoints = getObjPoints();
    vector<Point2f> imgPoints(points, points + 9);

    //����PnP
    solvePnP(objPoints, imgPoints, cameraMatrix, disCoeffs, rvecCamera2Obj, tvecCamera2Obj);

    //������ͶӰ���
    caculateError();

    //��Ŀ���
    distanceSolver(demo);

    //����ŷ����
    eulerSolver(demo);
}

void Ranger::setCameraMatrix(Mat CM) {
    cameraMatrix = move(CM);
}

void Ranger::setDisCoeffs(Mat DC) {
    disCoeffs = move(DC);
}

