#include "display.hpp"

Display::Display()
{
}

void Display::update()
{
}

void Display::receiveData()
{
}

void Display::sendData()
{
    byte buffer[SEND_PACKET_SIZE];

    buffer[0] = data.speed;
    buffer[1] = data.mode << 4 | data.brake << 3 | data.gear;
    buffer[2] = data.engineTemp;
    buffer[3] = data.controllerTemp;
    buffer[4] = data.batteryTemp;
    buffer[5] = data.batteryVoltage >> 8;
    buffer[6] = data.batteryVoltage;

    displaySerial.write(buffer, SEND_PACKET_SIZE);
}
