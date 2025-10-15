#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // кнопка
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  bool buttonPressed = digitalRead(2) == HIGH;

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" | Y: ");
  Serial.print(y);
  Serial.print(" | Button: ");
  Serial.println(buttonPressed ? "Pressed" : "Released");

  delay(200);
}
