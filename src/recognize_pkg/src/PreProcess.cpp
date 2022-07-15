//
// Created by wjy on 22-7-10.
//

#include "recognize_pkg/PreProcess.h"

#include <utility>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"

using namespace cv;

void PreProcess::myUndistort(Mat cameraMatrix, Mat distCoeffs, Mat &input) {
    Mat mask = input.clone();
    undistort(mask, input, cameraMatrix, distCoeffs);
}

Mat PreProcess::start(Color color, Mat cameraMatrix, Mat distCoeffs, Mat& input) {
    //原图
    Mat demo;
    //滤波输出
    Mat blurDst;
    //二值化输出
    Mat binaryDst;
    //边缘图
    Mat edge;
    myUndistort(std::move(cameraMatrix), std::move(distCoeffs), input);
    Mat* channels = new Mat[3];
    //通道分离
    split(input, channels);
    //颜色选取
    if (color == RED) {
        demo = channels[2] - channels[0];
    } else {
        demo = channels[0] - channels[2];
    }
    delete [] channels;
    blurDst = demo.clone();
    //高斯模糊去噪点
    GaussianBlur(demo, blurDst, Size(5, 5), 5);
    threshold(blurDst, binaryDst, 150, 255, THRESH_BINARY);
    //寻找边缘
    Canny(binaryDst, edge, 0, 255);
    namedWindow("Pre", WINDOW_NORMAL);
    imshow("Pre", binaryDst);
    return binaryDst;
}
