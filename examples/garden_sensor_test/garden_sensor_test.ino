// ============================================================
//  Garden Sensor TEST  — confirms DHT11 + moisture read OK
//  DHT11 on GPIO4 · moisture (Duinotech analog out) on GPIO34
// ============================================================

#include "DHT.h"

#define DHTPIN 4          // DHT11 data pin
#define DHTTYPE DHT11     // <-- MUST be DHT11, not DHT22
#define MOISTUREPIN 34    // Duinotech analog out

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Garden sensor test starting...");
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();   // Celsius

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT11: FAILED to read  (wiring or wrong sensor type)");
  } else {
    Serial.print("Temp: ");     Serial.print(t);
    Serial.print(" C   Humidity: "); Serial.print(h);
    Serial.println(" %");
  }

  int moisture = analogRead(MOISTUREPIN);   // 0–4095 on ESP32
  Serial.print("Moisture (raw): ");
  Serial.println(moisture);
  Serial.println("-----------------------------");

  delay(2500);   // DHT11 needs ~2s between reads
}
