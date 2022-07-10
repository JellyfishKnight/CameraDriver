//
// Created by wjy on 22-7-10.
//

#include "PreProcess.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

using namespace cv;

Mat PreProcess::start(Color color, Mat& input) {
    Mat demo;
    Mat blurDst;
    Mat binaryDst;
    Mat edge;
    Mat* channels = new Mat[3];
    split(input, channels);              //ͨ������
    if (color == RED) {
        demo = channels[2] - channels[0];
    } else {
        demo = channels[0] - channels[2];
    }
    delete [] channels;
    blurDst = demo.clone();
    /*�о�����ģ����Ч����಻��*/
//    medianBlur(demo, blurDst, 5);       //��ֵģ��ȥ�����
    GaussianBlur(demo, blurDst, Size(5, 5), 5);    //��˹ģ��ȥ���
    threshold(blurDst, binaryDst, 80, 255, THRESH_BINARY);
    Canny(binaryDst, edge, 35, 135);                   //���Կ��Ǵ��Ľ�
    namedWindow("Pre", WINDOW_NORMAL);
    imshow("Pre", edge);
    return edge;
}
