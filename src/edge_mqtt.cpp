#include "edge_mqtt.h"
#include <WiFi.h>
#include <WiFiClientSecure.h> // <-- Use the Secure client
#include <PubSubClient.h>

#if __has_include("secrets.h")
#include "secrets.h"
#else
#include "secrets.example.h"
#endif

// Pulling the token from our auth logic
extern String getEdgeToken(); 

// Replace WiFiClient with WiFiClientSecure
WiFiClientSecure espClient;
PubSubClient mqttClient(espClient);

// Circuit Breaker Variables
int connectionAttempts = 0;
const int MAX_ATTEMPTS = 5;
unsigned long initialBackoffMs = 5000; // Start with 5 seconds

void setupMQTT() {
    // 1. Load the Root CA to verify Weaver's identity
    espClient.setCACert(CA_CERT);
    
    // 2. Load the ESP32's identity to prove who we are to Weaver
    espClient.setCertificate(CLIENT_CERT);
    espClient.setPrivateKey(CLIENT_KEY);

    // 3. Set the server to the secure port (8883)
    mqttClient.setServer(WEAVER_MQTT_IP, 8883); 
    
    // Optional: Increase timeout for the heavy TLS handshake
    mqttClient.setKeepAlive(60);
}

void connectToWeaver() {
    while (!mqttClient.connected()) {
        if (connectionAttempts >= MAX_ATTEMPTS) {
            Serial.println("\n[CRITICAL] Max connection attempts breached. Tripping circuit breaker!");
            Serial.println("Entering Deep Sleep for 1 hour to preserve battery bank...");
            
            // 3600 seconds = 1 hour. Convert to microseconds for ESP32
            uint64_t sleepDurationUS = 3600ULL * 1000000ULL;
            ESP.deepSleep(sleepDurationUS);
        }

        Serial.printf("\n[mTLS] Attempting secure handshake with Weaver (Attempt %d/%d)...\n", 
                      connectionAttempts + 1, MAX_ATTEMPTS);
        
        // The Handshake: We still pass the JWT as an extra application-layer check
        String jwt = getEdgeToken();
        if (mqttClient.connect("ManaKai_Sensor_01", "edge_node", jwt.c_str())) {
            Serial.println("[SUCCESS] Secure mTLS Tunnel Established!");
            connectionAttempts = 0; // Reset counter on successful link
        } else {
            connectionAttempts++;
            
            // Calculate exponential backoff delay: initialDelay * 2^(attempts-1)
            unsigned long currentBackoff = initialBackoffMs * (1 << (connectionAttempts - 1));
            
            Serial.printf("[FAILURE] MQTT State: %d. Retrying in %lu seconds...\n", 
                          mqttClient.state(), currentBackoff / 1000);
            
            delay(currentBackoff);
        }
    }
}


void publishSensorData(float soilMoisture) {
    if (!mqttClient.connected()) {
        connectToWeaver();
    }
    mqttClient.loop();
    
    String payload = String("{\"moisture\":") + soilMoisture + "}";
    mqttClient.publish("manakai/soil/node01", payload.c_str());
    Serial.println("Encrypted data published to Sovereign Stack.");
}

