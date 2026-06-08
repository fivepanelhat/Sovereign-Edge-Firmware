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
        Serial.print("Initiating mTLS connection to Weaver...");
        
        // The Handshake: We still pass the JWT as an extra application-layer check
        String jwt = getEdgeToken();
        if (mqttClient.connect("ManaKai_Sensor_01", "edge_node", jwt.c_str())) {
            Serial.println("Secure mTLS Tunnel Established!");
        } else {
            Serial.print("Failed, state: ");
            Serial.print(mqttClient.state());
            // A state of -2 usually means the certificate verification failed
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
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

