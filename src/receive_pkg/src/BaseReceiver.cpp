//
// Created by wjy on 22-7-9.
//

#include "receive_pkg/BaseReceiver.h"
#include "iostream"

using namespace std;

void BaseReceiver::subscribe(void (*p)(Mat)) {
    cout << "Base Mat Subscribe" << endl;
}

void BaseReceiver::subscribe(void (*p)(int)) {
    cout << "Base Int32 Subscribe" << endl;
}