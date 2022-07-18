//
// Created by wjy on 22-7-10.
//

#ifndef SRC_SYSTEM_H
#define SRC_SYSTEM_H

#include <utility>
#include "publish_pkg/ImgPublisher.h"
#include "PreProcess.h"
#include "Ranger.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "vector"

#define maxLenRatio 10

#define minLenRatio 3

#define maxAngleError 5

#define maxAreaRation 2

#define minImageRatio 0.5

#define maxImageRatio 2


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
    //����������ĵ����Ƕ�
    float angleI{}, angleJ{};
    //֡��
    static float FPS;
    //������
//    Int32Receiver* int32Receiver{};
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
    void RectFit(Mat& src);

    /**
     * @brief �����Ƕ��Է�������
     * @param a ��ת����
     * @return ������ĽǶ�
     */
    float adjustAngle(const RotatedRect& a);

    /**
     * @brief ɸѡװ�װ�����
     * @param a
     * @param b
     * @return true ͨ��ɸѡ
     * @return false ��ͨ��ɸѡ
     */
    bool selectionOfRects(const RotatedRect& a, const RotatedRect& b);

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
//        int32Receiver = new Int32Receiver("NumberBack");
    }

    /**
     * @brief ����ʶ��ϵͳ
     */
    static void Start(Mat demo);
    /**
     * @brief ���غ���,������Ƶ����
     */
    static void Start();

    /**
     * @brief ������,�ͷ��ڴ�
     */
    ~System() {
        delete imgPublisher;
//        delete int32Receiver;
    }

};



#endif //SRC_SYSTEM_H
