#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);                // CE=9, CSN=10

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setAddressWidth(5);
  radio.setChannel(76);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(false);
  radio.disableDynamicPayloads();
  radio.setPayloadSize(32);

  const uint8_t addr[5] = {'0','0','0','0','1'};
  radio.openWritingPipe(addr);
  radio.stopListening();
  radio.flush_tx(); radio.flush_rx();
}

void loop() {
  char msg[32] = "Hello";
  bool ok = radio.write(&msg, sizeof(msg));
  Serial.println(ok ? "Sent OK" : "Send FAIL");
  delay(500);
}
