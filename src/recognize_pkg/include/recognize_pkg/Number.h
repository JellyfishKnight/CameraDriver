//
// Created by wjy on 22-7-22.
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
    explicit Number(string saveroot) : saveRoot(move(saveroot)) {
        //ʹ��δ����ʼ����ʵ������ģ��
        svm = StatModel::load<SVM>(saveRoot);
    }
    /**
     * @brief ��ʼʶ��
     * @param numberImage װ�װ�����ͼƬ
     */
    int start(Mat numberImage);
};

#endif //SRC_NUMBER_H
