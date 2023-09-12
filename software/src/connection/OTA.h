#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>

namespace OTA
{
    long unsigned int lastTime = 0;
    int interval = 1000;

    bool setupOTA()
    {
        ArduinoOTA.setHostname("SBV-CTRL");

        WiFi.mode(WIFI_STA);
        WiFi.begin("SBV-CTRL", "12345678");

        if (WiFi.waitForConnectResult(2000) != WL_CONNECTED)
        {
            WiFi.mode(WIFI_OFF);
            WiFi.disconnect();
            ArduinoOTA.end();
            return false;
        }

        ArduinoOTA.begin();
        ArduinoOTA.handle();

        return true;
    }

    void handle()
    {
        if (millis() < lastTime)
            lastTime = millis();

        if (millis() - lastTime > interval)
        {
            ArduinoOTA.handle();
            lastTime = millis();
        }
    }
}
