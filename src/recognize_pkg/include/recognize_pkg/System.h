//
// Created by wjy on 22-7-10.
//

#ifndef SRC_SYSTEM_H
#define SRC_SYSTEM_H

#include <utility>
#include "PreProcess.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "vector"

using namespace std;
using namespace cv;

class System {
private:
    //静态指针指向当前对象
    static System* pThis;
    //视频路径 (也可以从相机接收)
    string root;
    //敌方颜色
    Color color;
    //原图
    Mat demo;
    //所有找到的轮廓
    vector<vector<Point>> allContours;
    //轮廓层级
    vector<Vec4i> hierarchy;
    //筛选过后的轮廓
    vector<vector<Point>> selectedContours;
    //所有被筛选过后的轮廓拟合的矩形
    vector<RotatedRect> allRects;
    //匹配上的两个矩形
    RotatedRect matchA, matchB;
    //装甲板中心
    Point center;
    /**
     * @brief 找到轮廓并且进行筛选
     * @param frame 输入图像,应当为二值化图像
     */
    void ContoursFind(const Mat& frame);

    /**
     * @brief 拟合矩形并且进行匹配
     */
    void RectFit(Mat& demo);

public:
    /**
     * @brief 构造器
     * @param r 视频输入路径
     * @param c 敌方装甲板颜色
     */
    explicit System(string  r = "NULL", Color c = BLUE) : root(std::move(r)), color(c) {
        pThis = this;
    }

    /**
     * @brief 启动识别系统
     */
    static void Start(Mat demo);
    /**
     * @brief 重载函数,用于视频调试
     */
    static void Start();

    ~System() = default;

};



#endif //SRC_SYSTEM_H
