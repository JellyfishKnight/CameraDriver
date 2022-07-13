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

/**
 *
 * @param root
 * @param images
 * @param labels
 */
void Number::LoadData() {
    cout << "Loading images and labels to vector." << endl;
    for (int i = 1; i <= class_num; ++i) {
        string num_str = to_string(i);
        for (int j = 0; j < max_index; ++j) {
            //寻找图片文件
            string filename = samples::findFile(readRoot + num_str + "/" + to_string(j) + ".png",false, true);
            //判空
            if (filename.empty()) {
                continue;
            }
            total_images[i]++;
            //读图
            Mat input = imread(filename, IMREAD_GRAYSCALE);

            Mat image;
            // 转成能训练的格式，1.0/255为缩放因子
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
 * @brief 扰乱数据集
 * @param image_set
 * @param label_set
 */
void Number::Shuffle(vector<Mat> &image_set, vector<int> &label_set, vector<string> &name_set) {
    // 随机数字索引向量
    vector<int> shuffled_indices(image_set.size());
    for (size_t i = 0; i < image_set.size(); i++) {
        shuffled_indices[i] = (int) i;
    }
    // 随机打乱索引数组
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(shuffled_indices.begin(), shuffled_indices.end(), std::default_random_engine(seed));

    vector<Mat> shuffled_digits;
    vector<int> shuffled_labels;
    vector<string> shuffled_names;

    for (int index : shuffled_indices) {
        shuffled_digits.push_back(image_set[index]);//根据打乱的索引数组 生成小数字图像向量
        shuffled_labels.push_back(label_set[index]);//根据打乱的索引数组 生成小数字图像的标签向量
        shuffled_names.push_back(name_set[index]);  //根据打乱的索引数组 生成小数字图像的文件名向量
    }

    image_set = shuffled_digits;//更新整体数字图像为打乱顺序的数字图像
    label_set = shuffled_labels;//更新标签向量为 打乱顺序的数字图像对应的标签
    name_set = shuffled_names;//更新文件名向量为 打乱顺序的数字图像对应的文件名
}

/**
 * @brief 分裂训练测试
 * @param image_set
 * @param label_set
 * @param train_images
 * @param train_labels
 * @param test_images
 * @param test_labels
 */
void Number::SplitTrainTest(vector<Mat> image_set, vector<int> label_set, vector<string> name_set,
                    vector<Mat> &train_images, vector<int> &train_labels,
                    vector<Mat> &test_images, vector<int> &test_labels, vector<string> &test_names) {
    int cnt[15]{};
    // 随机打乱
    Shuffle(image_set, label_set, name_set);
    for (int i = 0; i < image_set.size(); ++i) {
        // 训练集占比可以调整
        if (cnt[label_set[i]] < total_images[label_set[i]] * train_ratio) {
            // 转换成一行输入
            train_images.push_back(image_set[i].reshape(0, 1));
            train_labels.push_back(label_set[i]);
            cnt[label_set[i]]++;
        } else {
            // 转换成一行输入
            test_images.push_back(image_set[i].reshape(0, 1));
            test_labels.push_back(label_set[i]);
            test_names.push_back(name_set[i]);
        }
    }
}

float Number::EvaluateModel(vector<float> output, vector<string> names) {
    int total_correct = 0;
    for (int i = 0; i < output.size(); ++i) {
        if (lround(output[i]) == labels[i]) {
            // 统计正确数量
            correct_result[labels[i]]++;
            total_correct++;
        } else {
            cout << "Wrong prediction on " << names[i] << ".\n";
            // 统计到第i类错误数量
            wrong_result[labels[i]]++;
        }
    }
    return (float)total_correct / output.size();
}

void Number::start(const Mat& numberImage, Mat& demo) {
    //加载数据
    LoadData();

    // 循环100次测试参数(C, gamma)性能
    double correct_rate = 0;
    int test_num = 1;
    for (int i = 0; i < test_num; i++) {
        vector<Mat> train_images;
        vector<int> train_labels;
        vector<Mat> test_images;
        vector<int> test_labels;
        // 测试集文件名，用于找到错误的图片名字
        vector<string> test_names;

        // 分割训练集测试集
        SplitTrainTest(images, labels, file_names,
                       train_images, train_labels, test_images, test_labels, test_names);
        // 合并成一个图片使API能Predict
        Mat train_image, test_image;
        vconcat(train_images, train_image);
        vconcat(test_images, test_image);
        // SVM参数设置和训练
        Ptr<SVM> svm;
        svm = SVM::create();
        svm->setType(SVM::C_SVC);
        svm->setKernel(SVM::RBF);
        svm->setGamma(0.025);
        svm->setC(7);
        svm->train(train_image, ml::ROW_SAMPLE, train_labels);
        svm->save("/home/wjy/Projects/RMlearning/CameraDriverWS/src/Datas/SVM.xml");
        // 预测和评估模型
        vector<float> svm_output;
        svm->predict(test_image, svm_output);
        double temp_correct_rate = EvaluateModel(svm_output, test_names);
        correct_rate += temp_correct_rate / test_num;
    }
    for (int i = 1; i <= class_num; ++i) {
        printf("Average number of wrong predictions on class %d is %.0f.\n", i,
               round((float) wrong_result[i] / test_num));
    }
    cout << "Correct rate of SVM on test set is: " << correct_rate * 100 << "%." << endl;
//    // kNN方法
//    Ptr<KNearest> kNN;
//    kNN = KNearest::create();
//    kNN->train(train_image, ml::ROW_SAMPLE, train_labels);
//    vector<float> kNN_output;
//    kNN->findNearest(test_image, 5, kNN_output);
//    correct_rate = EvaluateModel(kNN_output, test_labels, test_names);
//    cout << "Correct rate of kNN on test set is: " << correct_rate * 100 << "%." << endl;
}
