#include "display.h"

using namespace Communication;
using namespace Display_Private;

void Display::init()
{
    displaySerial.begin(baudRate, SERIAL_8N1, displayRXPin, displayTXPin);
}

void Display::handle()
{
    // Prevent rollower
    if (millis() < lastReceive)
        lastReceive = millis();

    // Control update interval
    if (millis() - lastReceive >= receiveInterval)
    {
        if (displaySerial.available() > 4)
        {
            Packet packet(displaySerial);
        }

        lastReceive = millis();
    }

    // Handle sending data

    // Prevent rollower
    if (millis() < lastSend)
        lastSend = millis();

    // Control update interval
    if (millis() - lastSend >= sendInterval)
    {
        sendData();

        lastSend = millis();
    }
}

// Done for now
void Display::sendData()
{
    switch (data.mode)
    {
    case MODE::MAIN:
        sendMainData();
        break;
    case MODE::TORQUE:
        sendTorqueData();
        break;
    }
}

// Done for now
void Display::sendMainData()
{
    byte buffer[11];

    byte size = 8;
    byte mode = (byte)MODE::MAIN;
    byte speed = data.mainData.speed & 0xFF;
    byte batteryVoltage = (data.mainData.batteryVoltage) >> 8;
    byte batteryVoltage2 = (data.mainData.batteryVoltage) & 0xFF;
    byte gear = data.mainData.gear;
    byte engineTemperature = uint8_t(data.mainData.engineTemperature);
    byte batteryTemperature = uint8_t(data.mainData.controllerTemperature);
    byte controllerTemperature = uint8_t(data.mainData.batteryTemperature);

    buffer[0] = startByte;
    buffer[1] = size;
    buffer[2] = mode;
    buffer[3] = speed;
    buffer[4] = batteryVoltage;
    buffer[5] = batteryVoltage2;
    buffer[6] = gear;
    buffer[7] = engineTemperature;
    buffer[8] = controllerTemperature;
    buffer[9] = batteryTemperature;
    buffer[10] = calculateChecksum(buffer, 11);

    displaySerial.write(buffer, 11);
}

// Done for now
void Display::sendTorqueData()
{
    byte buffer[8];

    byte size = 5;
    byte mode = (byte)MODE::TORQUE;
    byte torque = data.torqueData.torque & 0xFF;
    byte gear = data.mainData.gear;
    byte engineTemperature = uint8_t(data.mainData.engineTemperature);
    byte controllerTemperature = uint8_t(data.mainData.controllerTemperature);

    buffer[0] = startByte;
    buffer[1] = size;
    buffer[2] = mode;
    buffer[3] = torque;
    buffer[4] = gear;
    buffer[5] = engineTemperature;
    buffer[6] = controllerTemperature;
    buffer[7] = calculateChecksum(buffer, 8);

    displaySerial.write(buffer, 8);
}

Packet::Packet(HardwareSerial &serial)
{
    while (serial.peek() != 65)
    {
        serial.read();
        if (serial.available() <= 0)
            return;
    }

    int startByte = serial.read();
    int size = serial.read();
    packet = {startByte, (unsigned char)size};

    if (size < 1)
    {
        packet.clear();
        return;
    }

    for (int i = 0; i < size; i++)
    {
        packet.push_back(serial.read());
    }

    byte checksum = serial.read();
    packet.push_back(checksum);

    if (checksum != calculateChecksum(packet.data(), packet.size()))
    {
        packet.clear();
        return;
    }

    PACKET_TYPE packetType = (PACKET_TYPE)packet[2];

    // Remove startByte, size, packet type and checksum
    packet.erase(packet.begin(), packet.begin() + 3);
    packet.pop_back();

    switch (packetType)
    {
    case PACKET_TYPE::CHANGE_MODE:
        changeMode();
        break;
    case PACKET_TYPE::GEAR_CONTROL:
        gearControl();
        break;
    case PACKET_TYPE::BRAKE:
        brake();
        break;
    case PACKET_TYPE::GET_PARAM:
        break;
    case PACKET_TYPE::SET_PARAM:
        break;
    case PACKET_TYPE::POWER_ON:
        break;
    case PACKET_TYPE::POWER_OFF:
        break;
    };

    packet.clear();
}

// Done
void Packet::changeMode()
{
    MODE mode = (MODE)packet[0];

    switch (mode)
    {
    case MODE::MENU:
        data.mode = MODE::MENU;
        break;
    case MODE::MAIN:
        data.mode = MODE::MAIN;
        break;
    case MODE::TORQUE:
        data.mode = MODE::TORQUE;
        break;
    case MODE::SETTINGS:
        data.mode = MODE::SETTINGS;
        break;
    case MODE::DATA:
        data.mode = MODE::DATA;
        break;
    default:
        data.mode = MODE::MENU;
        break;
    };
};

// Done for now
void Packet::gearControl()
{
    GEAR_CONTROL action = (GEAR_CONTROL)packet[0];

    switch (action)
    {
    case GEAR_CONTROL::INCREASE_GEAR:
        if (data.mainData.gear < 5)
            data.mainData.gear++;
        controller.changeGear();
        break;
    case GEAR_CONTROL::DECREASE_GEAR:
        if (data.mainData.gear > 0)
            data.mainData.gear--;
        controller.changeGear();
        break;
    default:
        break;
    };
}

// Done
void Packet::brake()
{
    BRAKE type = (BRAKE)packet[0];

    switch (type)
    {
    case BRAKE::RELEASE_BRAKE:
        data.brake = false;
        break;
    case BRAKE::BRAKE:
        data.brake = true;
        break;
    };
}
