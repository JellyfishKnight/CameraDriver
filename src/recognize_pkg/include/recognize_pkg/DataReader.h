//
// Created by wjy on 22-7-10.
//

#ifndef SRC_DATAREADER_H
#define SRC_DATAREADER_H

#include "opencv2/core/core.hpp"
#include "string"

using namespace std;
using namespace cv;

class DataReader {
private:
    //文件读取器指针
    FileStorage* fileStorage{};

    string root;
public:
    /**
     * @brief 构造器
     * @param root 文件路径
     */
    explicit DataReader(string  r);
    /**
     * @brief 开始读取数据
     * @param cameraMat 相机内参矩阵
     * @param distCoeff 相机畸变矩阵
     * @return true 读取成功
     * @return false 读取失败
     */
    bool readData(Mat& cameraMat, Mat& distCoeff);
    /**
     * @brief 析构器
     */
    ~DataReader() {
        delete fileStorage;
    }
};


#endif //SRC_DATAREADER_H
