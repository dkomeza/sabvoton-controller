#ifndef IO_H
#define IO_H

#include <Arduino.h>

#include "data/data.h"

namespace IO_Constants
{
    // Pin definitions
    const uint8_t VOLTAGE_REFERENCE_PIN = 26;
    const uint8_t BATTERY_TEMPERATE_PIN = 32;
    const uint8_t CONTROLLER_TEMPERATURE_PIN = 27;
    const uint8_t ENGINE_TEMPERATURE_PIN = 34;
    const uint8_t TORQUE_SENSOR_PIN = 33;
    const uint8_t BATTERY_VOLTAGE_PIN = 35;
    const uint8_t ROTATION_SENSOR_PIN = 23;

    // Voltage reference
    const float VOLTAGE_REFERENCE = 1.8;
    const int VOLTAGE_REFERENCE_SAMPLES = 20;

    // Temperature
    const int THERMISTOR_R1 = 10000;
    const int THERMISTOR_R2 = 10000;
    const int THERMISTOR_NOMINAL_TEMPERATURE = 20;
    const int THERMISTOR_BETA = 3435;
    const int THERMISTOR_SAMPLES = 10;

    // Torque sensor
    const int TORQUE_SENSOR_SAMPLES = 10;
    const float TORQUE_SENSOR_MIN = 1.55;
    const float TORQUE_SENSOR_MAX = 3.0;

    // Battery voltage
    const int BATTERY_VOLTAGE_SAMPLES = 10;
    const float DIVIDER_R1 = 1000.0;
    const float DIVIDER_R2 = 33.0;

    // Rotation sensor
    const float RPM_TO_KMH = 0.1885;
}

struct Temperature
{
    int engine = 0;
    int controller = 0;
    int battery = 0;
};

class IO
{
public:
    void setup();
    void handle();

private:
    long unsigned int lastVoltageTime = 0;
    long unsigned int lastTemperatureTime = 0;
    long unsigned int lastTorqueTime = 0;

    int voltageInterval = 500;
    int temperatureInterval = 500;
    int torqueInterval = 20;
    

    void getTemperature();
    void getTorque();
    void getBatteryVoltage();

    int voltageOffset = 0;
    void getVoltageOffset();

    int readThermistor(int pin);
    int convertThermistor(float temperature);

    uint16_t readAnalogPin(int pin, int samples);
};

#endif