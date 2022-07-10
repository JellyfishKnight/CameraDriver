//
// Created by wjy on 22-7-10.
//

#ifndef SRC_PREPROCESS_H
#define SRC_PREPROCESS_H

#include "opencv2/core.hpp"

using namespace cv;

typedef enum color {BLUE, RED} Color;

/*工具类,不可实例化*/

class PreProcess {
private:
    ~PreProcess() = default;
    PreProcess() = default;
public:
    /**
     * @brief 预处理静态函数
     * @param color 敌方的颜色
     * @param input 输入图片
     */
    static Mat start(Color color, Mat& input);
};

#endif //SRC_PREPROCESS_H
