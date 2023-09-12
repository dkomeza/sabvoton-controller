#include "io.h"

using namespace IO_Constants;

void IO::setup()
{
    // Set up pins
    pinMode(BATTERY_VOLTAGE_PIN, INPUT);
    pinMode(VOLTAGE_REFERENCE_PIN, INPUT);
    pinMode(BATTERY_TEMPERATE_PIN, INPUT);
    pinMode(CONTROLLER_TEMPERATURE_PIN, INPUT);
    pinMode(ENGINE_TEMPERATURE_PIN, INPUT);
    pinMode(TORQUE_SENSOR_PIN, INPUT);
    pinMode(ROTATION_SENSOR_PIN, INPUT);

    // Set up the voltage reference
    getVoltageOffset();
}

void IO::handle()
{
    if (millis() < lastVoltageTime)
        lastVoltageTime = millis();

    if (millis() - lastVoltageTime >= voltageInterval)
    {
        getBatteryVoltage();
        lastVoltageTime = millis();
    }

    if (millis() < lastTemperatureTime)
        lastTemperatureTime = millis();

    if (millis() - lastTemperatureTime >= temperatureInterval)
    {
        getTemperature();
        lastTemperatureTime = millis();
    }

    if (millis() < lastTorqueTime)
        lastTorqueTime = millis();

    if (millis() - lastTorqueTime >= torqueInterval)
    {
        getTorque();
        lastTorqueTime = millis();
    }
}

void IO::getVoltageOffset()
{
    // Map the voltage reference to 0-4095
    int reference = map(VOLTAGE_REFERENCE * 1000, 0, 3300, 0, 4095);

    // Read the voltage reference
    int voltage = 0;
    for (int i = 0; i < VOLTAGE_REFERENCE_SAMPLES; i++)
    {
        voltage += analogRead(VOLTAGE_REFERENCE_PIN);
    }
    voltage /= VOLTAGE_REFERENCE_SAMPLES;

    // Calculate the offset
    voltageOffset = reference - voltage;
}

void IO::getTemperature()
{
    data.mainData.engineTemperature = readThermistor(ENGINE_TEMPERATURE_PIN);
    data.mainData.controllerTemperature = readThermistor(CONTROLLER_TEMPERATURE_PIN);
    data.mainData.batteryTemperature = readThermistor(BATTERY_TEMPERATE_PIN);
}

int IO::readThermistor(int pin)
{
    float temperature = readAnalogPin(pin, THERMISTOR_SAMPLES);

    return convertThermistor(temperature);
}

int IO::convertThermistor(float temperature)
{
    float temp = 4095 / temperature - 1;
    temp = THERMISTOR_R1 / temp;
    temp = temp / THERMISTOR_R2;

    temp = log(temp);
    temp /= THERMISTOR_BETA;

    temp += 1.0 / (THERMISTOR_NOMINAL_TEMPERATURE + 273.15);
    temp = 1.0 / temp;
    temp -= 273.15;

    return temp;
}

void IO::getTorque()
{
    uint16_t torque = readAnalogPin(TORQUE_SENSOR_PIN, TORQUE_SENSOR_SAMPLES);

    double torqueValue = (torque * 3.3 / 4095 - TORQUE_SENSOR_MIN) * 1000;

    int torqueOutput = map(torqueValue, 0, (TORQUE_SENSOR_MAX - TORQUE_SENSOR_MIN) * 1000, 0, 255);

    if (torqueOutput < 0)
        torqueOutput = 0;
    else if (torqueOutput > 255)
        torqueOutput = 255;

    data.torque = torqueOutput;
}

void IO::getBatteryVoltage()
{
    uint16_t voltage = readAnalogPin(BATTERY_VOLTAGE_PIN, BATTERY_VOLTAGE_SAMPLES);

    double voltageValue = (voltage * 3.3 / 4095) * (DIVIDER_R1 + DIVIDER_R2) / DIVIDER_R2;

    data.mainData.batteryVoltage = voltageValue * 10;
}

uint16_t IO::readAnalogPin(int pin, int samples)
{
    uint16_t value = 0;
    for (int i = 0; i < samples; i++)
    {
        value += analogRead(pin);
    }
    value /= samples;
    value += voltageOffset;

    return value;
}
