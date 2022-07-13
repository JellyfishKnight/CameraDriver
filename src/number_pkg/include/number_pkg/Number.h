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
    // 类别数目
    const int class_num = 8;
    // 训练集占比
    const double train_ratio = 0.1;
    // 每个类别最多样本数量
    const int max_index = 1000;
    //每个类别总样本数，正确分类样本数，错误分类样本数
    int total_images[15]{}, correct_result[15]{}, wrong_result[15]{};
    /**
     * @brief 图片数据加载
     */
    void LoadData(const string &data_path);
    //图片集
    vector<Mat> images;
    //
    vector<int> labels;
    //图片文件名称
    vector<string> file_names;
    /**
     * @brief 数据扰乱
     */
    void Shuffle();
    /**
     * @brief 分裂数据集
     */
    void SplitTrainTest();
    //训练图片集
    vector<Mat> train_images;
    vector<int> train_labels;
    //测试图片集
    vector<Mat> test_images;
    vector<int> test_labels;
    /**
     * @brief 评估模型
     * @param output 预测结果
     * @param labels 标签
     * @param names 测试集文件名，用于找到错误的图片名字
     * @return 错误率
     */
    float EvaluateModel(vector<float> output);
    vector<string> test_names;
public:
    /**
     * @brief 构造器
     * @param r 训练图片路径
     * @param classNum 类别数目
     * @param trainRatio 训练集占比
     * @param maxIndex 每个类别最多样本数量
     */
    explicit Number(string rr, string sr, int classNum = 8, double trainRatio = 0.1, int maxIndex = 1000) :
        readRoot(move(rr)), saveRoot(move(sr)), class_num(classNum), train_ratio(trainRatio), max_index(maxIndex) {
        pThis = this;
    }
    /**
     * @brief 开始识别
     * @param numberImage 装甲板数字图片
     */
    static void start(Mat numberImage);
    /**
     * @brief 重载函数,测试用
     */
    static void start();

    ~Number() = default;
};



#endif //SRC_NUMBER_H
