//
// Created by wjy on 22-7-10.
//

#ifndef SRC_SYSTEM_H
#define SRC_SYSTEM_H

#include <utility>
#include "publish_pkg/ImgPublisher.h"
#include "PreProcess.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "vector"

using namespace std;
using namespace cv;

class System {
private:
    //��ָ̬��ָ��ǰ����
    static System* pThis;
    //��Ƶ·�� (Ҳ���Դ��������)
    string root;
    //��������ļ�·��
    string dataRoot;
    //�з���ɫ
    Color color;
    //����ڲξ����Լ��������
    Mat cameraMatrix, disCoeffs;
    //ԭͼ
    Mat demo;
    //��ֵ�����
    Mat binaryDst;
    //�����ҵ�������
    vector<vector<Point>> allContours;
    //�����㼶
    vector<Vec4i> hierarchy;
    //ɸѡ���������
    vector<vector<Point>> selectedContours;
    //���б�ɸѡ�����������ϵľ���
    vector<RotatedRect> allRects;
    //ƥ���ϵ���������
    RotatedRect matchA, matchB;
    //װ�װ�����
    Point center;
    //֡��
    static float FPS;
    //������
    ImgPublisher* imgPublisher{};
    //����ROI�����ȡ��ԭͼ
    Mat ROINeeded;
    /**
     * @brief ���ݶ�ȡ
     * @return true �ɹ���ȡ
     * @return false ��ȡʧ��
     */
    static bool DataRead();
    /**
     * @brief �ҵ��������ҽ���ɸѡ
     * @param frame ����ͼ��,Ӧ��Ϊ��ֵ��ͼ��
     */
    void ContoursFind(const Mat& frame);

    /**
     * @brief ��Ͼ��β��ҽ���ƥ��
     */
    void RectFit(Mat& demo);
public:
    /**
     * @brief ������
     * @param r ��Ƶ����·��
     * @param c �з�װ�װ���ɫ
     */
    explicit System(string  fr = "NULL", Color c = BLUE, string dr = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/CameraData.xml") :
    root(std::move(fr)), dataRoot(move(dr)), color(c) {
        pThis = this;
        DataRead();
        imgPublisher = new ImgPublisher("Number", 10000);
    }

    /**
     * @brief ����ʶ��ϵͳ
     */
    static void Start(Mat demo);
    /**
     * @brief ���غ���,������Ƶ����
     */
    static void Start();

    ~System() = default;

};



#endif //SRC_SYSTEM_H
