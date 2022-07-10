//
// Created by wjy on 22-7-10.
//

#ifndef SRC_SYSTEM_H
#define SRC_SYSTEM_H

#include <utility>
#include "PreProcess.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "vector"

using namespace std;
using namespace cv;

class System {
private:
    static System* pThis;
    //��Ƶ·�� (Ҳ���Դ��������)
    string root;
    //�з���ɫ
    Color color;
    //ԭͼ
    Mat demo;
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
    /**
     * @brief �ҵ��������ҽ���ɸѡ
     * @param frame ����ͼ��,Ӧ��Ϊ��ֵ��ͼ��
     */
    void ContoursFind(const Mat& frame);

    /**
     * @brief ��Ͼ��β��ҽ���ƥ��
     */
    void RectFit();

public:
    /**
     * @brief ������
     * @param r ��Ƶ����·��
     * @param c �з�װ�װ���ɫ
     */
    explicit System(string  r = "NULL", Color c = BLUE) : root(std::move(r)), color(c) {
        pThis = this;
    }

    /**
     * @brief ����ʶ��ϵͳ
     */
    void Start();

    /**
     * @brief ����Receiver��ͼ��
     * @param input ����ͼ��
     */
    static void Receive(Mat input);

    ~System() = default;

};



#endif //SRC_SYSTEM_H
