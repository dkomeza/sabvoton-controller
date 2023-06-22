#include <Arduino.h>

#include "./connection/OTA.hpp"

#include "./display/display.hpp"
#include "./controller/controller.hpp"
#include "./io/io.hpp"

Display display;
Controller controller;
IO io;

void handleDelay(long now);

void setup()
{
  IPAddress ip = setupOTA();
}

void loop()
{
  long now = millis();

  io.update();
  controller.update();
  display.update();

  ArduinoOTA.handle();

  handleDelay(now); // Ensure consistent loop time
}

void handleDelay(long now)
{
  long time_diff = millis() - now;
  int delay_time = 10 - time_diff;

  while (delay_time < 0)
  {
    delay_time += 10;
  }

  delay(delay_time);
}