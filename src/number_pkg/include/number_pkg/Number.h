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
    //训练图片路径
    string root;
    // 类别数目
    const int class_num = 8;
    // 训练集占比
    const double train_ratio = 0.1;
    // 每个类别最多样本数量
    const int max_index = 1000;
    //每个类别总样本数，正确分类样本数，错误分类样本数
    int total_images[15]{}, correct_result[15]{}, wrong_result[15]{};
    /**
     * @brief 数据加载
     */
    void LoadData();
    //图片集
    vector<Mat> images;
    //
    vector<int> labels;
    //图片文件名称
    vector<string> file_names;
    /**
     * @brief 数据扰乱
     * @param image_set
     * @param label_set
     * @param name_set
     */
    void Shuffle(vector<Mat> &image_set, vector<int> &label_set, vector<string> &name_set)
public:
    /**
     * @brief 构造器
     * @param r 训练图片路径
     * @param classNum 类别数目
     * @param trainRatio 训练集占比
     * @param maxIndex 每个类别最多样本数量
     */
    explicit Number(string r, int classNum = 8, double trainRatio = 0.1, int maxIndex = 1000) :
        root(std::move(r)), class_num(classNum), train_ratio(trainRatio), max_index(maxIndex) {}
    /**
     * @brief 开始识别
     * @param numberImage 装甲板数字图片
     */
    void start(Mat numberImage);

};



#endif //SRC_NUMBER_H
