#include "controller.hpp"

void Controller::update()
{
    setPower(data.power);

    if (!data.power)
        return;

    setGear(data.gear);
    setThrottle(data.throttle);
    setSoftStart(data.softStart);
}

void Controller::setPower(bool _power)
{
    if (power == _power)
        return;

    digitalWrite(POWER_PIN, _power);

    power = _power;
}

void Controller::setGear(int _gear)
{
    if (gear == _gear)
        return;

    switch (_gear)
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

    gear = _gear;
}

void Controller::setThrottle(int _throttle)
{
    if (_throttle == throttle)
        return;

    if (data.brake)
    {
        _throttle = 0;
        dacWrite(THROTTLE_PIN, 0);
        return;
    }

    int throttleValue = getThrottleValue(_throttle);

    dacWrite(THROTTLE_PIN, throttleValue);

    throttle = _throttle;
}

void Controller::setSoftStart(bool _softStart)
{
    if (softStart == _softStart)
        return;

    digitalWrite(SOFT_START_PIN, _softStart);

    softStart = _softStart;
}

int Controller::getThrottleValue(int throttle)
{
    return map(throttle, 0, 100, 0, MAX_THROTTLE);
}