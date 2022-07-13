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
    string readRoot;
    //���ݱ���·��
    string saveRoot;
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
    void Shuffle(vector<Mat> &image_set, vector<int> &label_set, vector<string> &name_set);
    /**
     * @brief �������ݼ�
     * @param image_set
     * @param label_set
     * @param name_set
     * @param train_images
     * @param train_labels
     * @param test_images
     * @param test_labels
     * @param test_names
     */
    void SplitTrainTest(vector<Mat> image_set, vector<int> label_set, vector<string> name_set,
                                vector<Mat> &train_images, vector<int> &train_labels,
                                vector<Mat> &test_images, vector<int> &test_labels, vector<string> &test_names);
    /**
     * @brief ����ģ��
     * @param output
     * @param labels
     * @param names
     * @return ��ȷ�ʴ�С
     */
    float EvaluateModel(vector<float> output, vector<string> names);
public:
    /**
     * @brief ������
     * @param r ѵ��ͼƬ·��
     * @param classNum �����Ŀ
     * @param trainRatio ѵ����ռ��
     * @param maxIndex ÿ����������������
     */
    explicit Number(string rr, string sr, int classNum = 8, double trainRatio = 0.1, int maxIndex = 1000) :
        readRoot(move(rr)), saveRoot(move(sr)), class_num(classNum), train_ratio(trainRatio), max_index(maxIndex) {}
    /**
     * @brief ��ʼʶ��
     * @param numberImage װ�װ�����ͼƬ
     */
    void start(const Mat& numberImage, Mat& demo);

    ~Number() = default;
};



#endif //SRC_NUMBER_H
