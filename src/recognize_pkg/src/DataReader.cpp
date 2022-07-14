//
// Created by wjy on 22-7-10.
//
#include "recognize_pkg/DataReader.h"

#include <utility>
#include "opencv2/core/core.hpp"
#include "iostream"

using namespace std;
using namespace cv;

DataReader::DataReader(string  r) : root(std::move(r)) {}

bool DataReader::readData(Mat &cameraMat, Mat &distCoeff) {
    //初始化文件读取器
    fileStorage = new FileStorage(root, FileStorage::READ);
    if (fileStorage->isOpened()) {
        //读取
        (*fileStorage)["Intrinsic_Matrix_MV"] >> cameraMat;
        (*fileStorage)["Distortion_Coefficients_MV"] >> distCoeff;
        return true;
    } else {
//        cout << "Data file root wrong!" << endl;
        return false;
    }
}

