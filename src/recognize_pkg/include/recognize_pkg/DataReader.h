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
    //�ļ���ȡ��ָ��
    FileStorage* fileStorage{};

    string root;
public:
    /**
     * @brief ������
     * @param root �ļ�·��
     */
    explicit DataReader(string  r);
    /**
     * @brief ��ʼ��ȡ����
     * @param cameraMat ����ڲξ���
     * @param distCoeff ����������
     * @return true ��ȡ�ɹ�
     * @return false ��ȡʧ��
     */
    bool readData(Mat& cameraMat, Mat& distCoeff);
    /**
     * @brief ������
     */
    ~DataReader() {
        delete fileStorage;
    }
};


#endif //SRC_DATAREADER_H
