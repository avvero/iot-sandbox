#include <Arduino.h>
#include "PowerFunctions.h"

#define IR_PIN 3
PowerFunctions pf(IR_PIN, 0);

// Joystick
#define JOY_X A0
#define JOY_Y A1
#define JOY_BTN 7

const int deadZone = 60;
const int maxSpeed = 7;
const int refresh = 40;  // ms

int L = 0, R = 0;
unsigned long lastSend = 0;

int stick(int v) {
  v -= 512;
  if (abs(v) < deadZone) return 0;
  v = map(v, -512, 512, -maxSpeed, maxSpeed);
  return constrain(v, -maxSpeed, maxSpeed);
}

void driveLR(int l, int r) {
  pf.single_pwm(PowerFunctionsPort::RED,  pf.speedToPwm(l * 15));
  pf.single_pwm(PowerFunctionsPort::BLUE, pf.speedToPwm(r * 15));
  lastSend = millis();
}

void brake() {
  pf.single_pwm(PowerFunctionsPort::RED,  PowerFunctionsPwm::BRAKE);
  pf.single_pwm(PowerFunctionsPort::BLUE, PowerFunctionsPwm::BRAKE);
}

void setup() {
  pinMode(JOY_BTN, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int X = stick(analogRead(JOY_X));
  int Y = stick(analogRead(JOY_Y));

  bool turbo = (digitalRead(JOY_BTN) == LOW);

  int targetL = constrain(Y + X, -maxSpeed, maxSpeed);
  int targetR = constrain(Y - X, -maxSpeed, maxSpeed);

  if (turbo) {
    if (targetL != 0) targetL = (targetL > 0 ? maxSpeed : -maxSpeed);
    if (targetR != 0) targetR = (targetR > 0 ? maxSpeed : -maxSpeed);
  }

  // Fail-safe: если джойстик в центре → стоп
  if (targetL == 0 && targetR == 0) {
    brake();
    delay(refresh);
    return;
  }

  driveLR(targetL, targetR);
  delay(refresh);

  // Fail-safe: потеря связи → стоп
  if (millis() - lastSend > 500) {
    brake();
  }
}
