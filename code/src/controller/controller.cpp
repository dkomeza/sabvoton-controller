#include "controller.hpp"

void Controller::setPower(bool power) {
    if (power == _power) return;

    _power = power;
}

void Controller::setGear(int gear) {
    if (gear == _gear) return;

    _gear = gear;
}

void Controller::setThrottle(int throttle) {
    if (throttle == _throttle) return;

    _throttle = throttle;
}

void Controller::setSoftStart(bool softStart) {
    if (softStart == _softStart) return;

    _softStart = softStart;
}

int Controller::getVoltage() {
    return _voltage;
}