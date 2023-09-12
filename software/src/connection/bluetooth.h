#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothSerial.h>

namespace Bluetooth_Constants
{
    enum Message_ID
    {
        ID_PING = 0x01,
        ID_SETTINGS = 0x02,
        ID_CONTROL = 0x03,
        ID_STATUS = 0x04,
    };

    enum INSTRUCTION_SETTINGS
    {
        INS_SETTINGS_THROTTLE = 0x01,
    };

    enum PARAMS_THROTTLE
    {
        PARAMS_THROTTLE_MIN = 0x01,
        PARAMS_THROTTLE_MAX = 0x02,
        PARAMS_THROTTLE_SAVE = 0x03,
        PARAMS_THROTTLE_DISABLE = 0x04,
        PARAMS_THROTTLE_READ = 0x05,
    };
}

using namespace Bluetooth_Constants;

#include "data/data.h"
#include "controller/controller.h"

class Bluetooth
{
public:
    void setup();
    void write(uint8_t *data, size_t len);
    void write(uint8_t data);
    void print(String data);
    void println(String data);

    bool settingsEnabled = false;

private:
    BluetoothSerial SerialBT;
};

extern Bluetooth bluetooth;

#endif // BLUETOOTH_H