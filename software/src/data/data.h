#ifndef DATA_H
#define DATA_H

#include "display/communication.h"

using namespace Communication;

class Data
{
public:
    void init();

    MainData mainData;
    TorqueData torqueData;

    bool power = false;
    bool softStart = false;

    bool brake = false;

    int torque = 0;

    int voltageOffset = 0;

    MODE mode = MODE::MAIN;
};

extern Data data;

#endif