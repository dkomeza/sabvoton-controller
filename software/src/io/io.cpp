#include "io.hpp"

void IO::update()
{
    getTemperature();
    getVoltage();
    getTorque();
}

void IO::getTemperature()
{
    data.batteryTemp = readTemperature(BATTERY_TEMPERATURE_PIN);
    data.engineTemp = readTemperature(MOTOR_TEMPERATURE_PIN);
    data.controllerTemp = readTemperature(CONTROLLER_TEMPERATURE_PIN);
}

int IO::readTemperature(int pin)
{
    float temperature = 0;
    for (int i = 0; i < SAMPLE_COUNT; i++)
    {
        temperature += analogRead(pin);
    }

    temperature /= SAMPLE_COUNT;

    return convertTemperature(temperature);
}

int IO::convertTemperature(float _temperature)
{
    float temperature = 4095 / _temperature - 1;
    temperature = THERMISTOR_R1 / temperature;

    temperature = temperature / THERMISTOR_NOMINAL_RESISTANCE;
    temperature = log(temperature);
    temperature /= THERMISTOR_BETA;
    temperature += 1.0 / (THERMISTOR_NOMINAL_TEMPERATURE + 273.15);
    temperature = 1.0 / temperature;
    temperature -= 273.15;
    return temperature;
}

void IO::getVoltage()
{
    int voltage = analogRead(VOLTAGE_PIN);

    double voltageValue = voltage * 3.3 / 4095;

    long double voltageDivider = VOLTAGE_R2 / (VOLTAGE_R1 + VOLTAGE_R2);

    long double voltageDividerValue = voltageValue / voltageDivider;

    data.batteryVoltage = voltageDividerValue * 10;
}

void IO::getTorque()
{
    uint16_t torque = analogRead(TORQUE_SENSOR_PIN);

    double torqueValue = (torque * 3.3 / 4095 - TORQUE_VOLTAGE_MIN) * 1000;

    int torqueOutput = map(torqueValue, 0, (TORQUE_VOLTAGE_MAX - TORQUE_VOLTAGE_MIN) * 1000, 0, 256);

    data.torque = torqueOutput;
}
