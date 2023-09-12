#include <Arduino.h>
#include <EEPROM.h>

#include "connection/OTA.h"
#include "connection/bluetooth.h"

#include "data/data.h"
#include "controller/controller.h"
#include "io/io.h"
#include "display/display.h"

Data data;
Controller controller;
IO io;
Display display;
Bluetooth bluetooth;

long lastTime = 0;

bool isConnected = false;

void setup()
{
    Serial.begin(115200);

    // set up EEPROM
    EEPROM.begin(512);

    /* Set up OTA and check whether connected */
    isConnected = OTA::setupOTA();

    if (!isConnected)
    {
        data.init();
        io.setup();
        controller.setup();
        bluetooth.setup();
        display.init();

        data.mainData.gear = 3;
    }

    lastTime = millis();
}

void loop()
{
    if (isConnected)
    {
        OTA::handle();
    }
    else
    {
        if (!bluetooth.settingsEnabled)
        {
            io.handle();
            controller.handle();
            display.handle();
        }
    }

    delay(10);
}