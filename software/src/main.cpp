#include <Arduino.h>

#include "/connection/OTA.hpp"

#include "./io/io.hpp"

IO io;

void setup()
{
  IPAddress ip = setupOTA();
}

void loop()
{
  long now = millis();

  ArduinoOTA.handle();

  delay(10);
}