#ifndef BASEDRIVER_H
#define BASEDRIVER_H 

#include "opencv2/core/core.hpp"

class BaseDriver {                             //虚基类
protected:
    virtual void setCameraData() = 0;
    virtual bool grab() = 0;
public:
    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual void publish() = 0;
};

#endif //BASEDRIVER_H