#include <Arduino.h>

void setup() {
  pinMode(13, OUTPUT); // Встроенный светодиод на пине 13
}

void loop() {
  digitalWrite(13, HIGH); // Включить светодиод
  delay(100);            // Подождать 1 секунду
  digitalWrite(13, LOW);  // Выключить светодиод
  delay(100);            // Подождать 1 секунду
}