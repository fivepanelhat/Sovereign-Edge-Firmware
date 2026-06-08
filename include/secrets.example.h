// COASTAL ALPINE TECH: SECOPS WARNING
// DO NOT PUT REAL CREDENTIALS IN THIS FILE.
// Copy this file to 'secrets.h' (which is gitignored) and add your edge credentials.

#pragma once

const char* WIFI_SSID = "YOUR_LOCAL_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD"; // pragma: allowlist secret
const char* HARDWARE_SECRET = "GENERATE_DEVICE_SECRET_HERE"; // pragma: allowlist secret
const char* PORTAL_IP = "192.168.x.x";

// --- New Weaver Config ---
const char* WEAVER_MQTT_IP = "192.168.x.x";
const int WEAVER_MQTT_PORT = 1883;

// --- WEAVER mTLS CERTIFICATES ---

// 1. The Root CA that signed Weaver's broker certificate
const char* CA_CERT = R"EOF(
-----BEGIN CERTIFICATE-----
MIID... (Paste your CA cert here)
-----END CERTIFICATE-----
)EOF";

// 2. The ESP32's unique client certificate
const char* CLIENT_CERT = R"EOF(
-----BEGIN CERTIFICATE-----
MIID... (Paste your client cert here)
-----END CERTIFICATE-----
)EOF";

// 3. The ESP32's private key (KEEP THIS SAFE)
const char* CLIENT_KEY = R"EOF(
-----BEGIN RSA PRIVATE KEY----- // pragma: allowlist secret
MIIE... (Paste your private key here)
-----END RSA PRIVATE KEY-----
)EOF";


