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
            string filename = samples::findFile(root + num_str + "/" + to_string(j) + ".png",false, true);
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
 *
 * @param image_set
 * @param label_set
 */
void Shuffle(vector<Mat> &image_set, vector<int> &label_set, vector<string> &name_set) {
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
