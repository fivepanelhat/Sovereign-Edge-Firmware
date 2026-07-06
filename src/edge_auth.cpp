#include "edge_auth.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Preferences.h>
#include <ArduinoJson.h>

// Fallback to example header if local secrets.h is not found by developer
#if __has_include("secrets.h")
#include "secrets.h"
#else
#include "secrets.example.h"
#endif

// NVS Storage object
static Preferences preferences;
static String localJWT = "";
static bool nvsReady = false;

static void ensureNvs() {
  if (!nvsReady) {
    preferences.begin("auth", false);
    nvsReady = true;
  }
}

void connectSovereignNetwork() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to sovereign network");
  // ~30s cap so a dead AP doesn't hang boot forever
  for (int i = 0; i < 60 && WiFi.status() != WL_CONNECTED; i++) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\nWi-Fi connected. IP: %s\n", WiFi.localIP().toString().c_str());
  } else {
    Serial.println("\n[WARN] Wi-Fi connection timed out; auth will be skipped until reconnect.");
  }
}

void setupEdgeAuth() {
  ensureNvs();
  localJWT = preferences.getString("jwt", "");

  if (localJWT == "") {
    Serial.println("No JWT found in local NVS. Authenticating...");
    authenticateWithPortal();
  } else {
    Serial.println("JWT loaded successfully from NVS.");
  }
}

String getEdgeToken() {
  return localJWT;
}

void authenticateWithPortal() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Construct portal URL from secrets
    String authUrl = "http://" + String(PORTAL_IP) + ":3000/edge-auth";
    http.begin(authUrl);
    http.addHeader("Content-Type", "application/json");

    // Build the JSON payload using credentials in secrets.h
    StaticJsonDocument<200> doc;
    doc["deviceId"] = "ESP32_NODE_01";
    doc["hardwareSecret"] = HARDWARE_SECRET;
    
    String requestBody;
    serializeJson(doc, requestBody);

    // POST to the portal
    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode == 200) {
      String response = http.getString();

      // Parse the incoming JWT
      StaticJsonDocument<512> responseDoc;
      DeserializationError err = deserializeJson(responseDoc, response);
      const char* token = responseDoc["accessToken"];

      if (!err && token != nullptr) {
        localJWT = String(token);
        ensureNvs(); // NVS must be begun before any write
        preferences.putString("jwt", localJWT);
        Serial.println("Authentication successful. JWT saved to secure storage.");
      } else {
        Serial.println("Authentication response missing/invalid accessToken.");
      }
    } else {
      Serial.print("Authentication failed. HTTP status code: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
}
