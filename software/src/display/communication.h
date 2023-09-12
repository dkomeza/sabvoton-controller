#pragma once

#include <Arduino.h>

namespace Communication
{
    const int baudRate = 115200;

    const int startByte = 65;

    enum class PACKET_TYPE
    {
        CHANGE_MODE = 0x01,
        GEAR_CONTROL,
        BRAKE,
        GET_PARAM,
        SET_PARAM,
        POWER_ON,
        POWER_OFF,
    };

    enum class MODE
    {
        MENU = 0x00,
        MAIN,
        TORQUE,
        SETTINGS,
        DATA,
    };

    enum class GEAR_CONTROL
    {
        INCREASE_GEAR = 0x01,
        DECREASE_GEAR,
        START_WALK_MODE,
        STOP_WALK_MODE,
        START_CRUISE_CONTROL,
        STOP_CRUISE_CONTROL,
        INCREASE_CRUISE_CONTROL_SPEED,
        DECREASE_CRUISE_CONTROL_SPEED,
    };

    enum class BRAKE
    {
        RELEASE_BRAKE = 0x00,
        BRAKE = 0x01,
    };

    struct MainData
    {
        int speed;
        int batteryVoltage;
        int gear;
        int engineTemperature;
        int controllerTemperature;
        int batteryTemperature;
    };

    struct TorqueData
    {
        int torque;
        int gear;
        int engineTemperature;
        int controllerTemperature;
    };

    byte calculateChecksum(byte buff[], int size);
}