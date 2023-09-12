#include "bluetooth.h"

void handlePacket(const uint8_t *data, size_t len);
void handleSettings(const uint8_t *data, size_t len);
void handleThrottleSettings(const uint8_t *data, size_t len);

void Bluetooth::setup()
{
    SerialBT.begin("SBV-CTRL");
    SerialBT.onData(handlePacket);
}

void Bluetooth::write(uint8_t *data, size_t len)
{
    SerialBT.write(data, len);
}

void Bluetooth::write(uint8_t data)
{
    SerialBT.write(data);
}

void Bluetooth::print(String data)
{
    SerialBT.print(data);
}

void Bluetooth::println(String data)
{
    SerialBT.println(data);
}

void handlePacket(const uint8_t *data, size_t len)
{
    if (data[0] != 0x41)
    {
        return;
    }

    switch (data[1])
    {
    case ID_PING:
        bluetooth.println("PONG");
        break;
    case ID_SETTINGS:
        handleSettings(data, len);
        break;
    }
}

void handleSettings(const uint8_t *data, size_t len)
{
    bluetooth.settingsEnabled = true;
    switch (data[2])
    {
    case INS_SETTINGS_THROTTLE:
        handleThrottleSettings(data, len);
        break;
    }
}

void handleThrottleSettings(const uint8_t *data, size_t len)
{
    int value = 0;

    if (len >= 7)
    {
        value = data[4];
    }

    switch (data[3])
    {
    case PARAMS_THROTTLE_MIN:
        bluetooth.println("MIN: " + String(value));
        controller.setThrottleMin(value);
        break;
    case PARAMS_THROTTLE_MAX:
        bluetooth.println("MAX: " + String(value));
        controller.setThrottleMax(value);
        break;
    case PARAMS_THROTTLE_SAVE:
        bluetooth.println("SAVE");
        controller.saveThrottleSettings();
        bluetooth.settingsEnabled = false;
        break;
    case PARAMS_THROTTLE_DISABLE:
        bluetooth.println("DISABLE");
        controller.disableThrottle();
        break;
    case PARAMS_THROTTLE_READ:
        bluetooth.println("READ");
        int min = controller.readThrottleMin();
        int max = controller.readThrottleMax();
        bluetooth.println("MIN: " + String(min));
        bluetooth.println("MAX: " + String(max));
        break;
    }
}