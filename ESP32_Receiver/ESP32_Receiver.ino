#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "esp_wifi.h"

const int LED_PIN = 2;

// Runs whenever an ESP-NOW message is received
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {

  if (len > 0) {

    bool ledState = data[0];

    digitalWrite(LED_PIN, ledState ? HIGH : LOW);

    Serial.print("Received: ");

    if (ledState) {
      Serial.println("ON");
    } else {
      Serial.println("OFF");
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Set up LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Set Wi-Fi to Station mode
  WiFi.mode(WIFI_STA);

  // Use the same channel as the transmitter
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  // Start ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed!");
    return;
  }

  // Register the receive callback
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receiver ready.");
}

void loop() {
}