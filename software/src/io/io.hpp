#ifndef IO_H
#define IO_H

#include <Arduino.h>
#include "../data/data.hpp"

#define BATTERY_TEMPERATURE_PIN 32
#define MOTOR_TEMPERATURE_PIN 34
#define CONTROLLER_TEMPERATURE_PIN 27

#define THERMISTOR_R1 10000
#define THERMISTOR_NOMINAL_RESISTANCE 10000
#define THERMISTOR_NOMINAL_TEMPERATURE 25
#define THERMISTOR_BETA 3435
#define SAMPLE_COUNT 10

#define VOLTAGE_PIN 35
#define VOLTAGE_R1 1000000
#define VOLTAGE_R2 56000

#define TORQUE_SENSOR_PIN 33
#define TORQUE_VOLTAGE_MIN 1.5
#define TORQUE_VOLTAGE_MAX 3

struct Temperature
{
    int battery;
    int motor;
    int controller;
};

class IO
{
public:
    void update();

private:
    void getTemperature();
    void getVoltage();
    void getTorque();

    int readTemperature(int pin);
    int convertTemperature(float temperature);
};

extern IO io;

#endif