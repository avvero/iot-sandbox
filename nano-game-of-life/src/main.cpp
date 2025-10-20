#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

#define WIDTH 16   // клетки по горизонтали
#define HEIGHT 8   // клетки по вертикали

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

bool grid[WIDTH][HEIGHT];
bool newGrid[WIDTH][HEIGHT];

void setup() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // случайная генерация
  randomSeed(analogRead(0));
  for(int x=0; x<WIDTH; x++)
    for(int y=0; y<HEIGHT; y++)
      grid[x][y] = random(2);
}

int neighbors(int x, int y) {
  int n = 0;
  for(int dx=-1; dx<=1; dx++)
    for(int dy=-1; dy<=1; dy++)
      if(!(dx==0 && dy==0))
        if(grid[(x+dx+WIDTH)%WIDTH][(y+dy+HEIGHT)%HEIGHT]) n++;
  return n;
}

void loop() {
  // вычисляем новое поколение
  for(int x=0; x<WIDTH; x++)
    for(int y=0; y<HEIGHT; y++){
      int n = neighbors(x,y);
      newGrid[x][y] = (grid[x][y]) ? (n==2 || n==3) : (n==3);
    }

  // копируем
  for(int x=0; x<WIDTH; x++)
    for(int y=0; y<HEIGHT; y++)
      grid[x][y] = newGrid[x][y];

  // рисуем на OLED
  display.clearDisplay();
  for(int y=0; y<HEIGHT; y++){
    for(int x=0; x<WIDTH; x++){
      display.setCursor(x*8, y*8); // 8 пикселей на символ
      if(grid[x][y]) display.print(".");
    }
  }
  display.display();
  delay(200);
}
