#include <Arduino.h>
#include <WiFi.h>
#include "edge_auth.h"

#if __has_include("secrets.h")
#include "secrets.h"
#else
#include "secrets.example.h"
#endif

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect to Local Sovereign Network
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Network: ");
  Serial.println(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Sovereign Network.");

  // Authenticate edge node
  setupEdgeAuth();
}

void loop() {
  // Sensor logic & telemetry transmission goes here
  delay(5000);
}
