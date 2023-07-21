#include <Arduino.h>

#include "./connection/OTA.hpp"

#include "./display/display.hpp"
#include "./controller/controller.hpp"
#include "./io/io.hpp"
#include "./data/data.hpp"

Display display;
Controller controller;
IO io;
Data data;

bool is_connected = false;

void handleDelay(long now);

void setup()
{
  Serial.begin(115200);

  is_connected = setupOTA();

  Serial.println(is_connected);
}

void loop()
{
  long now = millis();

  if (!is_connected)
  {
    io.update();
    controller.update();
    display.update();
  }
  else
  {
    ArduinoOTA.handle();

    Serial.println("OTA");
  }

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