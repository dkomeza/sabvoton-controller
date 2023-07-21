#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>

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

    return true;
}