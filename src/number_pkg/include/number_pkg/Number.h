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
    //ѵ��ͼƬ·��
    string root;
    // �����Ŀ
    const int class_num = 8;
    // ѵ����ռ��
    const double train_ratio = 0.1;
    // ÿ����������������
    const int max_index = 1000;
    //ÿ�����������������ȷ�������������������������
    int total_images[15]{}, correct_result[15]{}, wrong_result[15]{};
    /**
     * @brief ���ݼ���
     */
    void LoadData();
    //ͼƬ��
    vector<Mat> images;
    //
    vector<int> labels;
    //ͼƬ�ļ�����
    vector<string> file_names;
    /**
     * @brief ��������
     * @param image_set
     * @param label_set
     * @param name_set
     */
    void Shuffle(vector<Mat> &image_set, vector<int> &label_set, vector<string> &name_set)
public:
    /**
     * @brief ������
     * @param r ѵ��ͼƬ·��
     * @param classNum �����Ŀ
     * @param trainRatio ѵ����ռ��
     * @param maxIndex ÿ����������������
     */
    explicit Number(string r, int classNum = 8, double trainRatio = 0.1, int maxIndex = 1000) :
        root(std::move(r)), class_num(classNum), train_ratio(trainRatio), max_index(maxIndex) {}
    /**
     * @brief ��ʼʶ��
     * @param numberImage װ�װ�����ͼƬ
     */
    void start(Mat numberImage);

};



#endif //SRC_NUMBER_H
