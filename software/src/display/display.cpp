#include "display.hpp"

Display::Display()
{
}

void Display::update()
{
}

void Display::receiveData()
{
    byte buffer[RECEIVE_PACKET_SIZE];

    if (displaySerial.available() < RECEIVE_PACKET_SIZE)
        return;

    displaySerial.readBytes(buffer, RECEIVE_PACKET_SIZE);

    data.mode = buffer[0] & 0b00010000;
    data.brake = buffer[0] & 0b00001000;
    data.gear = buffer[0] & 0b00000111;
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
