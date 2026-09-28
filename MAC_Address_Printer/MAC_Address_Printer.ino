#include <Arduino.h>
#include "esp_mac.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  uint8_t mac[6];

  // Read the factory-programmed Wi-Fi Station MAC address
  esp_read_mac(mac, ESP_MAC_WIFI_STA);

  Serial.print("Wi-Fi MAC Address: ");

  for (int i = 0; i < 6; i++) {
    if (i > 0) {
      Serial.print(":");
    }

    if (mac[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(mac[i], HEX);
  }

  Serial.println();
}

void loop() {
}