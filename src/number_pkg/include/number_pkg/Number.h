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
    //ѵ��ͼƬ·��
    string readRoot;
    //���ݱ���·��
    string saveRoot;
public:
    /**
     * @brief ������
     * @param rr ͼƬ·��
     * @param sr SVMѵ������·��
     */
    explicit Number(string rr, string sr, int classNum = 8, double trainRatio = 0.1, int maxIndex = 1000) :
        readRoot(move(rr)), saveRoot(move(sr)) {
        pThis = this;
    }
    /**
     * @brief ��ʼʶ��
     * @param numberImage װ�װ�����ͼƬ
     */
    static void start(Mat numberImage);

    ~Number() = default;
};



#endif //SRC_NUMBER_H
