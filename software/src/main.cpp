#include <Arduino.h>
#include "./io/io.hpp"

IO io;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(io.getTemperature().battery);
  delay(10);
}