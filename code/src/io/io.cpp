#include "io.hpp"

Temperature IO::getTemperature() {
    Temperature temperature;

    temperature.battery = readTemperature(BATTERY_TEMPERATURE_PIN);
    temperature.motor = readTemperature(MOTOR_TEMPERATURE_PIN);
    temperature.controller = readTemperature(CONTROLLER_TEMPERATURE_PIN);

    return temperature;
}

int IO::readTemperature(int pin) {
    float temperature = 0;
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        temperature += analogRead(pin);
    }

    temperature /= SAMPLE_COUNT;

    return convertTemperature(temperature);
}

int IO::convertTemperature(float _temperature) {
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