#include "controller.hpp"

void Controller::update()
{
}

void Controller::setPower(bool power)
{
    if (power == _power)
        return;

    digitalWrite(POWER_PIN, power);

    _power = power;
}

void Controller::setGear(int gear)
{
    if (gear == _gear)
        return;

    switch (gear)
    {
    case 0:
        digitalWrite(GEAR_LOW_PIN, HIGH);
        digitalWrite(GEAR_HIGH_PIN, LOW);
        break;
    case 1:
        digitalWrite(GEAR_LOW_PIN, LOW);
        digitalWrite(GEAR_HIGH_PIN, LOW);
        break;
    case 2:
        digitalWrite(GEAR_LOW_PIN, LOW);
        digitalWrite(GEAR_HIGH_PIN, HIGH);
        break;
    }

    _gear = gear;
}

void Controller::setThrottle(int throttle)
{
    if (throttle == _throttle)
        return;

    int throttleValue = getThrottleValue(throttle);

    dacWrite(THROTTLE_PIN, throttleValue);

    _throttle = throttle;
}

void Controller::setSoftStart(bool softStart)
{
    if (softStart == _softStart)
        return;

    digitalWrite(SOFT_START_PIN, softStart);

    _softStart = softStart;
}

int Controller::getThrottleValue(int throttle)
{
    return map(throttle, 0, 100, 0, MAX_THROTTLE);
}