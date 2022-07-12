//
// Created by wjy on 22-7-12.
//
//
// Created by 17703 on 2022/5/14.
//
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

// �����Ŀ
const int class_num = 8;
// ѵ����ռ��
const double train_ratio = 0.1;
// ÿ����������������
const int max_index = 1000;

//ÿ�����������������ȷ�������������������������
int total_images[15], correct_result[15], wrong_result[15];

/**
 *
 * @param data_path
 * @param images
 * @param labels
 */
void LoadData(const string &data_path, vector<Mat> &images, vector<int> &labels, vector<string> &file_names) {
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
 *
 * @param image_set
 * @param label_set
 */
void Shuffle(vector<Mat> &image_set, vector<int> &label_set, vector<string> &name_set) {
    // ���������������
    vector<int> shuffled_indices(image_set.size());
    for (size_t i = 0; i < image_set.size(); i++) {
        shuffled_indices[i] = (int) i;
    }
    // ���������������
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(shuffled_indices.begin(), shuffled_indices.end(), std::default_random_engine(seed));

    vector<Mat> shuffled_digits;
    vector<int> shuffled_labels;
    vector<string> shuffled_names;

    for (int index : shuffled_indices) {
        shuffled_digits.push_back(image_set[index]);//���ݴ��ҵ��������� ����С����ͼ������
        shuffled_labels.push_back(label_set[index]);//���ݴ��ҵ��������� ����С����ͼ��ı�ǩ����
        shuffled_names.push_back(name_set[index]);  //���ݴ��ҵ��������� ����С����ͼ����ļ�������
    }

    image_set = shuffled_digits;//������������ͼ��Ϊ����˳�������ͼ��
    label_set = shuffled_labels;//���±�ǩ����Ϊ ����˳�������ͼ���Ӧ�ı�ǩ
    name_set = shuffled_names;//�����ļ�������Ϊ ����˳�������ͼ���Ӧ���ļ���
}

/**
 *
 * @param image_set
 * @param label_set
 * @param train_images
 * @param train_labels
 * @param test_images
 * @param test_labels
 */
void SplitTrainTest(vector<Mat> image_set, vector<int> label_set, vector<string> name_set,
                    vector<Mat> &train_images, vector<int> &train_labels,
                    vector<Mat> &test_images, vector<int> &test_labels, vector<string> &test_names) {
    int cnt[15]{};
    // �������
    Shuffle(image_set, label_set, name_set);
    for (int i = 0; i < image_set.size(); ++i) {
        // ѵ����ռ�ȿ��Ե���
        if (cnt[label_set[i]] < total_images[label_set[i]] * train_ratio) {
            // ת����һ������
            train_images.push_back(image_set[i].reshape(0, 1));
            train_labels.push_back(label_set[i]);
            cnt[label_set[i]]++;
        } else {
            // ת����һ������
            test_images.push_back(image_set[i].reshape(0, 1));
            test_labels.push_back(label_set[i]);
            test_names.push_back(name_set[i]);
        }
    }
}

float EvaluateModel(vector<float> output, vector<int> labels, vector<string> names) {
    int total_correct = 0;
    for (int i = 0; i < output.size(); ++i) {
        if (lround(output[i]) == labels[i]) {
            // ͳ����ȷ����
            correct_result[labels[i]]++;
            total_correct++;
        } else {
            cout << "Wrong prediction on " << names[i] << ".\n";
            // ͳ�Ƶ���i���������
            wrong_result[labels[i]]++;
        }
    }
    return (float)total_correct / output.size();
}

int main() {
    string data_path = "/home/wjy/Projects/RMlearning/CameraDriverWS/src/number_pkg/src/SVM_img/";
    vector<Mat> images;
    vector<int> labels;
    vector<string> file_names;

    LoadData(data_path, images, labels, file_names);

    // ѭ��100�β��Բ���(C, gamma)����
    double correct_rate = 0;
    int test_num = 1;
    for (int i = 0; i < test_num; i++) {
        vector<Mat> train_images;
        vector<int> train_labels;
        vector<Mat> test_images;
        vector<int> test_labels;
        // ���Լ��ļ����������ҵ������ͼƬ����
        vector<string> test_names;

        // �ָ�ѵ�������Լ�
        SplitTrainTest(images, labels, file_names,
                       train_images, train_labels, test_images, test_labels, test_names);
        // �ϲ���һ��ͼƬʹAPI��Predict
        Mat train_image, test_image;
        vconcat(train_images, train_image);
        vconcat(test_images, test_image);
        // SVM�������ú�ѵ��
        Ptr<SVM> svm;
        svm = SVM::create();
        svm->setType(SVM::C_SVC);
        svm->setKernel(SVM::RBF);
        svm->setGamma(0.025);
        svm->setC(7);
        svm->train(train_image, ml::ROW_SAMPLE, train_labels);
        svm->save("/svm.xml");
        // Ԥ�������ģ��
        vector<float> svm_output;
        svm->predict(test_image, svm_output);
        double temp_correct_rate = EvaluateModel(svm_output, test_labels, test_names);
        correct_rate += temp_correct_rate / test_num;
    }
    for (int i = 1; i <= class_num; ++i) {
        printf("Average number of wrong predictions on class %d is %.0f.\n", i, round((float)wrong_result[i] / test_num));
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

    return 0;
}