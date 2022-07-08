#ifndef BASEDRIVER_H
#define BASEDRIVER_H 

class BaseDriver {                             //虚基类
protected:
    virtual void setCameraData() = 0;
public:
    virtual bool init() = 0;
};

#endif //BASEDRIVER_H