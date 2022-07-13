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
    // �����Ŀ
    const int class_num = 8;
    // ѵ����ռ��
    const double train_ratio = 0.1;
    // ÿ����������������
    const int max_index = 1000;
    //ÿ�����������������ȷ�������������������������
    int total_images[15]{}, correct_result[15]{}, wrong_result[15]{};
    /**
     * @brief ͼƬ���ݼ���
     */
    void LoadData(const string &data_path);
    //ͼƬ��
    vector<Mat> images;
    //
    vector<int> labels;
    //ͼƬ�ļ�����
    vector<string> file_names;
    /**
     * @brief ��������
     */
    void Shuffle();
    /**
     * @brief �������ݼ�
     */
    void SplitTrainTest();
    //ѵ��ͼƬ��
    vector<Mat> train_images;
    vector<int> train_labels;
    //����ͼƬ��
    vector<Mat> test_images;
    vector<int> test_labels;
    /**
     * @brief ����ģ��
     * @param output Ԥ����
     * @param labels ��ǩ
     * @param names ���Լ��ļ����������ҵ������ͼƬ����
     * @return ������
     */
    float EvaluateModel(vector<float> output);
    vector<string> test_names;
public:
    /**
     * @brief ������
     * @param r ѵ��ͼƬ·��
     * @param classNum �����Ŀ
     * @param trainRatio ѵ����ռ��
     * @param maxIndex ÿ����������������
     */
    explicit Number(string rr, string sr, int classNum = 8, double trainRatio = 0.1, int maxIndex = 1000) :
        readRoot(move(rr)), saveRoot(move(sr)), class_num(classNum), train_ratio(trainRatio), max_index(maxIndex) {
        pThis = this;
    }
    /**
     * @brief ��ʼʶ��
     * @param numberImage װ�װ�����ͼƬ
     */
    static void start(Mat numberImage);
    /**
     * @brief ���غ���,������
     */
    static void start();

    ~Number() = default;
};



#endif //SRC_NUMBER_H
