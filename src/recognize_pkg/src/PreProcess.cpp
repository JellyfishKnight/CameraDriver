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
    //ԭͼ
    Mat demo;
    //�˲����
    Mat blurDst;
    //��ֵ�����
    Mat binaryDst;
    //��Եͼ
    Mat edge;
    myUndistort(std::move(cameraMatrix), std::move(distCoeffs), input);
    Mat* channels = new Mat[3];
    //ͨ������
    split(input, channels);
    //��ɫѡȡ
    if (color == RED) {
        demo = channels[2] - channels[0];
    } else {
        demo = channels[0] - channels[2];
    }
    delete [] channels;
    blurDst = demo.clone();
    //��ֵģ��ȥ�����
    /*�о�����ģ����Ч����಻��*/
//    medianBlur(demo, blurDst, 5);
    //��˹ģ��ȥ���
    GaussianBlur(demo, blurDst, Size(5, 5), 5);
    threshold(blurDst, binaryDst, 150, 255, THRESH_BINARY);
    //Ѱ�ұ�Ե
    //���Կ��Ǵ��Ľ�
//    Canny(binaryDst, edge, 35, 135);
    namedWindow("Pre", WINDOW_NORMAL);
    imshow("Pre", binaryDst);
    return binaryDst;
}
