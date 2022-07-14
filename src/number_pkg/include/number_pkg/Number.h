//
// Created by wjy on 22-7-11.
//

#ifndef SRC_NUMBER_H
#define SRC_NUMBER_H
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/ml.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <string>

using namespace cv;
using namespace std;
using namespace ml;

class Number {
private:
    //ָ��ǰ����ľ�ָ̬��
    static Number* pThis;
    //���ݱ���·��
    string saveRoot;
    //���ڴ�Сת��������
    Mat maskOfReshape;
    //���������ͨ��
    Mat channels[3];
    //����Ԥ���ͼƬ
    Mat testImage;
    //SVMָ��
    Ptr<SVM> svm;
public:
    /**
     * @brief ������
     * @param saveroot SVMѵ������·��
     */
    explicit Number(string saveroot) :
        saveRoot(move(saveroot)) {
        pThis = this;
        //ʹ��δ����ʼ����ʵ������ģ��
        svm = StatModel::load<SVM>(pThis->saveRoot);
    }
    /**
     * @brief ��ʼʶ��
     * @param numberImage װ�װ�����ͼƬ
     */
    static void start(Mat numberImage);

    ~Number() = default;
};



#endif //SRC_NUMBER_H
