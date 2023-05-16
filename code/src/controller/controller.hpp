#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "../settings/settings.hpp"

#define POWER_PIN 4

#define GEAR_LOW_PIN 12
#define GEAR_HIGH_PIN 13

#define THROTTLE_PIN 25

#define MAX_THROTTLE 188

class Controller {
    public:
        void setPower(bool power);
        void setGear(int gear);
        void setThrottle(int throttle);
        void setSoftStart(bool softStart);
        int getVoltage();
    private:
        int _gear = 0;
        int _throttle = 0;
        bool _power = false;
        bool _softStart = true;
        int _voltage = 0;

        int getThrottleValue(int throttle);
};

extern Controller controller;

#endif
