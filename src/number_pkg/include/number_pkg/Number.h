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
    //数据保存路径
    string saveRoot;
    //用于大小转换的掩码
    Mat maskOfReshape;
    //分离的三个通道
    Mat channels[3];
    //用于预测的图片
    Mat testImage;
    //SVM指针
    Ptr<SVM> svm;
public:
    /**
     * @brief 构造器
     * @param saveroot SVM训练数据路径
     */
    explicit Number(string saveroot) :
        saveRoot(move(saveroot)) {
        pThis = this;
        //使用未经初始化的实例载入模型
        svm = StatModel::load<SVM>(pThis->saveRoot);
    }
    /**
     * @brief 开始识别
     * @param numberImage 装甲板数字图片
     */
    static void start(Mat numberImage);

    ~Number() = default;
};



#endif //SRC_NUMBER_H
