#include <Arduino.h>
#include "edge_auth.h"
#include "edge_mqtt.h"

void setup() {
    Serial.begin(115200);
    
    // 1. Connect to Wi-Fi & get the JWT from the Portal.
    // setupEdgeAuth initialises NVS then reuses a stored JWT or
    // authenticates; calling authenticateWithPortal directly wrote to
    // NVS before Preferences.begin() had ever run.
    connectSovereignNetwork();
    setupEdgeAuth();
    
    // 2. Prep the MQTT client
    setupMQTT();
}

void loop() {
    // Mocking a sensor reading from the microgreens
    float currentMoisture = 65.4; 
    
    publishSensorData(currentMoisture);
    
    // Deep sleep for 10 minutes to save battery
    // ESP.deepSleep(600e6); 
    delay(10000); // Using delay for testing purposes
}


