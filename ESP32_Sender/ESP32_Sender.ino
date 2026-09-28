#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "esp_wifi.h"

// MAC address of ESP32 #2 (receiver)
uint8_t receiverAddress[] = {
  0x68, 0x09, 0x47, 0x07, 0xB8, 0x24
};

void setup() {
  Serial.begin(115200);

  // Set Wi-Fi to Station mode
  WiFi.mode(WIFI_STA);

  // Both ESP32 boards must be on the same channel
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  // Start ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed!");
    return;
  }

  // Register the receiver as a peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add receiver!");
    return;
  }

  Serial.println("Transmitter ready.");
}

void loop() {

  // Send ON
  uint8_t message = 1;

  esp_err_t result = esp_now_send(
    receiverAddress,
    &message,
    sizeof(message)
  );

  if (result == ESP_OK) {
    Serial.println("Sent: ON");
  } else {
    Serial.println("Failed to send ON");
  }

  delay(2000);

  // Send OFF
  message = 0;

  result = esp_now_send(
    receiverAddress,
    &message,
    sizeof(message)
  );

  if (result == ESP_OK) {
    Serial.println("Sent: OFF");
  } else {
    Serial.println("Failed to send OFF");
  }

  delay(2000);
}