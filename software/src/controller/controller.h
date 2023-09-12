#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <EEPROM.h>

#include "data/data.h"

namespace Controller_Constants
{
    const int POWER_PIN = 4;

    const int GEAR_LOW_PIN = 12;
    const int GEAR_HIGH_PIN = 13;

    const int THROTTLE_PIN = 25;

    const int SOFT_START_PIN = 15;

    enum Gear
    {
        Low = 1,
        Medium = 2,
        High = 3
    };

    const int THROTTLE_MIN_ADDRESS = 11;
    const int THROTTLE_MAX_ADDRESS = 12;
}

using namespace Controller_Constants;

class Controller
{
public:
    void setup();
    void handle();

    void setThrottleMin(int value);
    void setThrottleMax(int value);
    void saveThrottleSettings();
    void disableThrottle();
    int readThrottleMin();
    int readThrottleMax();

    void changeGear();

private:
    long unsigned int lastTime = 0;
    int interval = 10;

    int THROTTLE_MIN = 0;
    int THROTTLE_MAX = 255;

    int throttleMin = 0;
    int throttleMax = 255;

    int torqueMin = 0;
    int torqueMax = 255;

    void handleThrottle();

    void setThrottle(int value);

    void setGear(Gear gear);
};

extern Controller controller;

#endif