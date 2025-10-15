#include <Arduino.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);

	while (!Serial)
		; // Wait for Serial to be ready

	delay(1000);
}

void loop() {
  static uint32_t t = 0;
  if (millis() - t >= 1000) {
    t += 1000;
    Serial.print(F("Hello World, t="));
    Serial.println(t);
  }
  //
  digitalWrite(LED_BUILTIN, HIGH);  // зажечь
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);   // погасить
  delay(500);
  //
  static String input;

  if (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      Serial.print("Got: ");
      Serial.println(input);
      input = "";               // сбросить
    } else {
      input += c;
    }
  }
}