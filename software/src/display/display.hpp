#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <HardwareSerial.h>

#include "../data/data.hpp"

#define SEND_PACKET_SIZE 7

class Display
{
public:
    Display()
    {
        displaySerial.begin(9600, SERIAL_8N1, 16, 17);
    };
    void update();

private:
    HardwareSerial displaySerial = HardwareSerial(2);

    void receiveData();
    void sendData();
};

extern Display display;

#endif
