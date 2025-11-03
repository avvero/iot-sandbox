#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremote.hpp>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define IR_RECEIVE_PIN 11

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {

      /*
        * Print a summary of received data
        */
      if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
          Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
          // We have an unknown protocol here, print extended info
          IrReceiver.printIRResultRawFormatted(&Serial, true);

          IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
      } else {
          IrReceiver.resume(); // Early enable receiving of the next IR frame

          IrReceiver.printIRResultShort(&Serial);
          IrReceiver.printIRSendUsage(&Serial);
      }
      Serial.println();

      /*
        * Finally, check the received data and perform actions according to the received command
        */
      if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
          Serial.println(F("Repeat received. Here you can repeat the same action as before."));
      } else {
          if (IrReceiver.decodedIRData.command == 0x10) {
              Serial.println(F("Received command 0x10."));
              // do something
          } else if (IrReceiver.decodedIRData.command == 0x11) {
              Serial.println(F("Received command 0x11."));
              // do something else
          }
      }
    }
}