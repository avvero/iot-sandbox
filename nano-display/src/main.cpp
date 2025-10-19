#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C адрес OLED, чаще всего 0x3C
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED не найден"));
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(1);      // размер текста
  display.setTextColor(SSD1306_WHITE); // цвет текста (OLED монохромный)
  display.setCursor(0,0);      // позиция текста
  display.println(", OLED!");
  display.display();            // показать на экране
}

void loop() {
  for(int i= 0; i < 128; i++){
    for (int j = 0; j < 64; j++) {
      display.clearDisplay();
      display.setCursor(i, j);
      display.println("#");
      display.display();
      delay(10);
    }
  }
}
