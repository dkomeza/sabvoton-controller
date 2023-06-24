#ifndef DATA_H
#define DATA_H

#include <Arduino.h>

/**
 * @brief Data class contains all data shared between the different modules
 */
class Data
{
public:
    unsigned int speed = 0;

    bool mode = false;
    bool brake = false;
    int gear = 0;

    int engineTemp = 0;
    int controllerTemp = 0;
    int batteryTemp = 0;

    long batteryVoltage = 0;

    bool power = false;
    bool softStart = true;

    int throttle = 0;
    int torque = 0;
};

extern Data data;

#endif