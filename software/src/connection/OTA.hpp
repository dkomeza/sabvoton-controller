#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>

IPAddress setupOTA()
{
    ArduinoOTA.setHostname("SBV-CTRL");

    WiFi.mode(WIFI_STA);
    WiFi.begin("SBV-CTRL", "12345678");

    WiFi.waitForConnectResult(5000);

    ArduinoOTA.begin();

    return WiFi.localIP();
}