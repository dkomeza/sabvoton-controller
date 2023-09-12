#include "controller.h"

void Controller::setup()
{
    // Set up pins
    pinMode(POWER_PIN, OUTPUT);
    pinMode(GEAR_LOW_PIN, OUTPUT);
    pinMode(GEAR_HIGH_PIN, OUTPUT);
    pinMode(THROTTLE_PIN, OUTPUT);
    pinMode(SOFT_START_PIN, OUTPUT);

    // Turn on the controller
    digitalWrite(POWER_PIN, HIGH);

    // Enable soft start
    digitalWrite(SOFT_START_PIN, LOW);

    // Set gear to neutral
    setGear(Gear::Medium);

    // Set throttle to 0
    setThrottle(0);

    // Read throttle settings from EEPROM
    THROTTLE_MIN = EEPROM.read(THROTTLE_MIN_ADDRESS);
    THROTTLE_MAX = EEPROM.read(THROTTLE_MAX_ADDRESS);

    // Update throttle based on gear
    changeGear();
}

void Controller::handle()
{
    // Return if in settings mode or empty mode
    if (data.mode == MODE::SETTINGS || data.mode == MODE::MENU)
        return;

    if (millis() < lastTime)
        lastTime = millis();

    if (millis() - lastTime < interval)
        return;

    // Update throttle
    handleThrottle();

    lastTime = millis();
}

void Controller::handleThrottle()
{
    if (data.brake || data.mainData.gear == 0 || data.torque == 0)
    {
        dacWrite(THROTTLE_PIN, 0);
        return;
    }

    int torqueValue = map(data.torque, torqueMin, torqueMax, 0, 255);

    if (torqueValue < 0)
        torqueValue = 0;
    else if (torqueValue > 255)
        torqueValue = 255;

    int throttleValue = map(torqueValue, 0, 255, THROTTLE_MIN, throttleMax);

    dacWrite(THROTTLE_PIN, throttleValue);
}

void Controller::changeGear()
{
    switch (data.mainData.gear)
    {
    case 1:
        throttleMax = (THROTTLE_MAX - THROTTLE_MIN) * 0.33 + THROTTLE_MIN;
        setGear(Low);
        torqueMax = 255;
        break;
    case 2:
        throttleMax = (THROTTLE_MAX - THROTTLE_MIN) * 0.66 + THROTTLE_MIN;
        setGear(Low);
        torqueMax = 255;
        break;
    case 3:
        throttleMax = THROTTLE_MAX;
        setGear(Low);
        torqueMax = 255;
        break;
    case 4:
        throttleMax = THROTTLE_MAX;
        setGear(Medium);
        torqueMax = 172;
        break;
    case 5:
        throttleMax = THROTTLE_MAX;
        setGear(High);
        torqueMax = 128;
        break;
    }
}

void Controller::setGear(Gear gear)
{
    switch (gear)
    {
    case Gear::Low:
        digitalWrite(GEAR_LOW_PIN, HIGH);
        digitalWrite(GEAR_HIGH_PIN, LOW);
        break;
    case Gear::Medium:
        digitalWrite(GEAR_LOW_PIN, LOW);
        digitalWrite(GEAR_HIGH_PIN, LOW);
        break;
    case Gear::High:
        digitalWrite(GEAR_LOW_PIN, LOW);
        digitalWrite(GEAR_HIGH_PIN, HIGH);
        break;
    }
}

void Controller::setThrottle(int value)
{
    dacWrite(THROTTLE_PIN, value);
}

void Controller::setThrottleMin(int value)
{
    THROTTLE_MIN = value;
    setThrottle(THROTTLE_MIN);
}

void Controller::setThrottleMax(int value)
{
    THROTTLE_MAX = value;
    setThrottle(THROTTLE_MAX);
}

void Controller::saveThrottleSettings()
{
    EEPROM.write(THROTTLE_MIN_ADDRESS, THROTTLE_MIN);
    EEPROM.write(THROTTLE_MAX_ADDRESS, THROTTLE_MAX);
    EEPROM.commit();
    setThrottle(0);
}

void Controller::disableThrottle()
{
    setThrottle(0);
}

int Controller::readThrottleMin()
{
    return THROTTLE_MIN;
}

int Controller::readThrottleMax()
{
    return THROTTLE_MAX;
}
