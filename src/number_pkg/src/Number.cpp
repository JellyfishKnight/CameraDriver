//
// Created by wjy on 22-7-11.
//
#include "number_pkg/Number.h"
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/ml.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;
using namespace cv;
using namespace ml;


Number* Number::pThis = nullptr;
/**
 *
 * @param root
 * @param images
 * @param labels
 */
void Number::LoadData(const string &data_path) {
    cout << "Loading images and labels to vector." << endl;

    for (int i = 1; i <= class_num; ++i) {
        string num_str = to_string(i);
        for (int j = 0; j < max_index; ++j) {
            //
            string filename = samples::findFile(data_path + num_str + "/" + to_string(j) + ".png",
                                                false, true);
            if (filename.empty()) {
                continue;
            }
            total_images[i]++;
            //
            Mat input = imread(filename, IMREAD_GRAYSCALE);

            Mat image;
            // ת����ѵ���ĸ�ʽ��1.0/255Ϊ��������
            input.convertTo(image, CV_32F, 1.0 / 255);

            images.push_back(image);
            labels.push_back(i);
            file_names.push_back(filename);
        }
        cout << "Find " << total_images[i] << " images in mark " << i << ".\n";
    }
    cout << "Finished loading." << endl;
}

/**
 * @brief �������ݼ�
 */
void Number::Shuffle() {
    // ���������������
    vector<int> shuffled_indices(images.size());
    for (size_t i = 0; i < images.size(); i++) {
        shuffled_indices[i] = (int) i;
    }
    // ���������������
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(shuffled_indices.begin(), shuffled_indices.end(), std::default_random_engine(seed));

    vector<Mat> shuffled_digits;
    vector<int> shuffled_labels;
    vector<string> shuffled_names;

    for (int index : shuffled_indices) {
        shuffled_digits.push_back(images[index]);//���ݴ��ҵ��������� ����С����ͼ������
        shuffled_labels.push_back(labels[index]);//���ݴ��ҵ��������� ����С����ͼ��ı�ǩ����
        shuffled_names.push_back(file_names[index]);  //���ݴ��ҵ��������� ����С����ͼ����ļ�������
    }
    images = shuffled_digits;//������������ͼ��Ϊ����˳�������ͼ��
    labels = shuffled_labels;//���±�ǩ����Ϊ ����˳�������ͼ���Ӧ�ı�ǩ
    file_names = shuffled_names;//�����ļ�������Ϊ ����˳�������ͼ���Ӧ���ļ���
}

/**
 * @brief ����ѵ������
 */
void Number::SplitTrainTest() {
    int cnt[15]{};
    // �������
    Shuffle();
    for (int i = 0; i < images.size(); ++i) {
        // ѵ����ռ�ȿ��Ե���
        if (cnt[labels[i]] < total_images[labels[i]] * train_ratio) {
            // ת����һ������
            train_images.push_back(images[i].reshape(0, 1));
            train_labels.push_back(labels[i]);
            cnt[labels[i]]++;
        } else {
            // ת����һ������
            test_images.push_back(images[i].reshape(0, 1));
            test_labels.push_back(labels[i]);
            test_names.push_back(file_names[i]);
        }
    }
}

float Number::EvaluateModel(vector<float> output) {
    int total_correct = 0;
    for (int i = 0; i < output.size(); ++i) {
        if (lround(output[i]) == test_labels[i]) {
            // ͳ����ȷ����
            correct_result[test_labels[i]]++;
            total_correct++;
        } else {
            cout << "Wrong prediction on " << test_names[i] << ".\n";
            // ͳ�Ƶ���i���������
            wrong_result[test_labels[i]]++;
        }
    }
    return (float)total_correct / output.size();
}

void Number::start(Mat numberImage) {
    pThis->LoadData(pThis->readRoot);

    // ѭ��100�β��Բ���(C, gamma)����
    double correct_rate = 0;
    int test_num = 1;
    for (int i = 0; i < test_num; i++) {
        // �ָ�ѵ�������Լ�
        pThis->SplitTrainTest();
        // �ϲ���һ��ͼƬʹAPI��Predict
        Mat train_image, test_image;
        vconcat(pThis->train_images, train_image);
        vconcat(pThis->test_images, test_image);
        // SVM�������ú�ѵ��
        Ptr<SVM> svm;
        svm = SVM::create();
        svm->setType(SVM::C_SVC);
        svm->setKernel(SVM::RBF);
        svm->setGamma(0.025);
        svm->setC(7);
        svm->train(train_image, ml::ROW_SAMPLE, pThis->train_labels);
        svm->save("../svm.xml");
        // Ԥ�������ģ��
        vector<float> svm_output;
        svm->predict(test_image, svm_output);
        double temp_correct_rate = pThis->EvaluateModel(svm_output);
        correct_rate += temp_correct_rate / test_num;
    }
    for (int i = 1; i <= pThis->class_num; ++i) {
        printf("Average number of wrong predictions on class %d is %.0f.\n", i, round((float)pThis->wrong_result[i] / test_num));
    }
    cout << "Correct rate of SVM on test set is: " << correct_rate * 100 << "%." << endl;
//    // kNN����
//    Ptr<KNearest> kNN;
//    kNN = KNearest::create();
//    kNN->train(train_image, ml::ROW_SAMPLE, train_labels);
//    vector<float> kNN_output;
//    kNN->findNearest(test_image, 5, kNN_output);
//    correct_rate = EvaluateModel(kNN_output, test_labels, test_names);
//    cout << "Correct rate of kNN on test set is: " << correct_rate * 100 << "%." << endl;
}

void Number::start() {
    pThis->LoadData(pThis->readRoot);

    // ѭ��100�β��Բ���(C, gamma)����
    double correct_rate = 0;
    int test_num = 1;
    for (int i = 0; i < test_num; i++) {
        // �ָ�ѵ�������Լ�
        pThis->SplitTrainTest();
        // �ϲ���һ��ͼƬʹAPI��Predict
        Mat train_image, test_image;
        vconcat(pThis->train_images, train_image);
        vconcat(pThis->test_images, test_image);
        // SVM�������ú�ѵ��
        Ptr<SVM> svm;
        svm = SVM::create();
        svm->setType(SVM::C_SVC);
        svm->setKernel(SVM::RBF);
        svm->setGamma(0.025);
        svm->setC(7);
        svm->train(train_image, ml::ROW_SAMPLE, pThis->train_labels);
        svm->save("../svm.xml");
        // Ԥ�������ģ��
        vector<float> svm_output;
        svm->predict(test_image, svm_output);
        double temp_correct_rate = pThis->EvaluateModel(svm_output);
        correct_rate += temp_correct_rate / test_num;
    }
    for (int i = 1; i <= pThis->class_num; ++i) {
        printf("Average number of wrong predictions on class %d is %.0f.\n", i, round((float)pThis->wrong_result[i] / test_num));
    }
    cout << "Correct rate of SVM on test set is: " << correct_rate * 100 << "%." << endl;


//    // kNN����
//    Ptr<KNearest> kNN;
//    kNN = KNearest::create();
//    kNN->train(train_image, ml::ROW_SAMPLE, train_labels);
//    vector<float> kNN_output;
//    kNN->findNearest(test_image, 5, kNN_output);
//    correct_rate = EvaluateModel(kNN_output, test_labels, test_names);
//    cout << "Correct rate of kNN on test set is: " << correct_rate * 100 << "%." << endl;
}

