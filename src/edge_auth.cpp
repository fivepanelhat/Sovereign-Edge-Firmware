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

void setupEdgeAuth() {
  preferences.begin("auth", false);
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
      deserializeJson(responseDoc, response);
      const char* token = responseDoc["accessToken"];
      
      localJWT = String(token);
      preferences.putString("jwt", localJWT);
      
      Serial.println("Authentication successful. JWT saved to secure storage.");
    } else {
      Serial.print("Authentication failed. HTTP status code: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  }
}
