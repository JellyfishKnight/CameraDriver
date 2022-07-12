//
// Created by wjy on 22-7-10.
//

#ifndef SRC_PREPROCESS_H
#define SRC_PREPROCESS_H

#include "opencv2/core.hpp"

using namespace cv;

typedef enum color {BLUE, RED} Color;

/*������,����ʵ����*/

class PreProcess {
private:
    ~PreProcess() = default;
    PreProcess() = default;

    static void myUndistort(Mat cameraMatrix, Mat distCoeffs, Mat& input);
public:
    /**
     * @brief Ԥ����̬����
     * @param color �з�����ɫ
     * @param input ����ͼƬ
     */
    static Mat start(Color color, Mat cameraMatrix, Mat distCoeffs, Mat& input);
};

#endif //SRC_PREPROCESS_H
