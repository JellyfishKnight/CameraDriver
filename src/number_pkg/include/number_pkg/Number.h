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
    //指向当前对象的静态指针
    static Number* pThis;
    //训练图片路径
    string readRoot;
    //数据保存路径
    string saveRoot;
public:
    /**
     * @brief 构造器
     * @param rr 图片路径
     * @param sr SVM训练数据路径
     */
    explicit Number(string rr, string sr, int classNum = 8, double trainRatio = 0.1, int maxIndex = 1000) :
        readRoot(move(rr)), saveRoot(move(sr)) {
        pThis = this;
    }
    /**
     * @brief 开始识别
     * @param numberImage 装甲板数字图片
     */
    static void start(Mat numberImage);

    ~Number() = default;
};



#endif //SRC_NUMBER_H
