#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "../settings/settings.hpp"

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
};

extern Controller controller;

#endif
