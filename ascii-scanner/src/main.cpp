#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const int minChannel = 0;
const int maxChannel = 125;
const int scanPasses = 100;

int channelHits[126];

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!radio.begin()) {
    Serial.println("NRF not found");
    while (1);
  }

  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(false);
  radio.disableCRC();

  Serial.println("nRF24L01+ Spectrum Scanner");
}

void loop() {
  memset(channelHits, 0, sizeof(channelHits));

  for (int pass = 0; pass < scanPasses; pass++) {
    for (int ch = minChannel; ch <= maxChannel; ch++) {
      radio.setChannel(ch);
      radio.startListening();
      delayMicroseconds(150);

      if (radio.testRPD()) {
        channelHits[ch]++;
      }
    }
  }

  for (int ch = minChannel; ch <= maxChannel; ch++) {
    int barLength = map(channelHits[ch], 0, scanPasses, 0, 60);
    if (barLength == 0) continue;

    float freqMHz = 2400.0 + ch;

    // Пример: "2476.00 MHz: #######"
    Serial.print(freqMHz, 2);
    Serial.print(" MHz: ");
    for (int i = 0; i < barLength; i++) {
      Serial.print("#");
    }
    Serial.println();
  }

  Serial.print("-");
  delay(1000);
}
