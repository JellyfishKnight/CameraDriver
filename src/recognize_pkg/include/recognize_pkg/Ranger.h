//
// Created by wjy on 22-7-10.
//

#ifndef SRC_RANGER_H
#define SRC_RANGER_H

#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

//������:����PnP,���ɱ�ʵ����
class Ranging {
private:
    //����ڲξ���
    Mat cameraMatrix;
    //�������
    Mat disCoeffs;
    //װ�װ�����ĵ��Լ����ĵ�
    Point2f *points;
    //װ�װ��ʵ�ʿ�Ⱥ͸߶�
    float boardWidth = 135;
    float boardHeight = 125;
    /**
     * @brief ��ʼ����Ա����
     */
    void init(const RotatedRect& a, const RotatedRect& b);
    /**
     * @brief ������������
     * @return ��������
     */
    vector<Point3f> getObjPoints();
    /**
     * @brief ������
     */
    void caculateError(Mat& rvec, Mat& tvec);

public:
    /**
     * @brief ��ʼ����PnP
     * @param a ����a
     * @param b ����b
     */
    void start(const RotatedRect& a, const RotatedRect& b, Mat& demo);

    Ranging() = default;

    ~Ranging() = default;
};


#endif //SRC_RANGER_H
