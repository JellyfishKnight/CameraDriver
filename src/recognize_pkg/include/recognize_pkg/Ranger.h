//
// Created by wjy on 22-7-10.
//

#ifndef SRC_RANGER_H
#define SRC_RANGER_H

#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

//������:����PnP,���ɱ�ʵ����
class Ranger {
private:
    //����ڲξ���
    Mat cameraMatrix;
    //�������
    Mat disCoeffs;
    //װ�װ�����ĵ��Լ����ĵ�
    Point2f *points{};
    //װ�װ�Ŀ��
    float imageWidth{};
    float imageHeight{};
    //װ�װ��ʵ�ʿ�Ⱥ͸߶�
    static float boardWidth;
    static float boardHeight;
    //��solvePnP���ص���ת������ƽ������
    Mat rvecCamera2Obj, tvecCamera2Obj;
    //ƽ�ƾ����������
    float tx{}, ty{}, tz{};
    //�����Ŀ���ľ���
    float distObj2Camera{};
    //͸�ӱ任����Ҫ�Ľǵ�
    Point2f pointsOfROI[4], pointsOfNumber[4];
    /**
     * @brief ��ʼ����Ա����
     */
    void init(const RotatedRect& a, const RotatedRect& b);

    /**
     * @brief �������˳��
     * @param angle ������Ƕ�
     * @param pointsA ������ĸ���
     * @param pointsB �ҵ����ĸ���
     */
    void adjustTheOrderOfPoints(float angle, Point2f pointsA[4], Point2f pointsB[4]);

    /**
     * @brief ������������
     * @return ��������
     */
    vector<Point3f> getObjPoints();

    /**
     * @brief ����װ�װ�ͼƬ�ĳ���
     */
    void calculateTheSizeOfImage();

    /**
     * @brief ������
     */
    void caculateError();
    /**
     * @brief ��Ŀ���
     * @param rvecCamera2Obj ���������ϵ����������ϵ����ת����
     * @param tvecCamera2Obj ���������ϵ����������ϵ��ƽ������
     * @param demo ԭͼ
     */
    void distanceSolver(Mat& demo);
    /**
     * @brief ����ŷ����
     * @param demo ԭͼ
     */
    void eulerSolver(Mat& demo);

public:
    /**
     * @brief ������
     * @param CM ����ڲξ���
     * @param DC ����������
     */
    Ranger(Mat& CM, Mat& DC) : cameraMatrix(CM), disCoeffs(DC) {}

    /**
     * @brief ��ʼ����PnP
     * @param a ����a
     * @param b ����b
     */
    void start(const RotatedRect& a, const RotatedRect& b, Mat& demo);
    /**
     * @brief ����װ�װ�ߴ�
     * @param number װ�װ�����
     */
    static void setBoardSize(int number = 4);
    /**
     * @brief ��ȡװ�װ�ROIͼ��
     * @param demo ԭͼ
     * @return װ�װ�ROI����
     */
    Mat getROI(Mat& demo);

    ~Ranger() = default;


};


#endif //SRC_RANGER_H
