#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>
#include <vector>

#include "data/data.h"
#include "connection/bluetooth.h"

#include "communication.h"

namespace Display_Private
{
    class Packet
    {
    public:
        Packet(HardwareSerial &serial);

    private:
        std::vector<byte> packet;

        void changeMode();
        void gearControl();
        void brake();
        void getParam();
        void setParam();
        void powerOn();
        void powerOff();
    };
}

class Display
{
public:
    void init();
    void handle();

private:
    const int displayRXPin = 16;
    const int displayTXPin = 17;

    HardwareSerial displaySerial = HardwareSerial(2);

    void sendData();

    // to change
    void sendMainData();
    void sendTorqueData();

    long unsigned int lastSend = 0;
    long unsigned int lastReceive = 0;
    int receiveInterval = 10;
    int sendInterval = 200;
};

extern Display display;