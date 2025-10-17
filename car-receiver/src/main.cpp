#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  pinMode(10, OUTPUT); // держим SPI в master
  if (!radio.begin()) Serial.println("radio.begin() FAIL");
  else Serial.println("radio.begin() OK");

  // Диагностика соединения по SPI
  Serial.print("isChipConnected: ");
  Serial.println(radio.isChipConnected() ? "YES" : "NO");

  radio.setChannel(76);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);   // начни с LOW/ MIN
  radio.setRetries(5, 15);
  radio.openReadingPipe(0, (const uint8_t*)"00001");
  radio.startListening();

  radio.printDetails(); // посмотри регистры
}

void loop() {
  if (radio.available()) {
    char buf[32] = {0};
    radio.read(buf, sizeof(buf));
    Serial.print("RX: ");
    Serial.println(buf);
  }
}