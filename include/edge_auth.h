#pragma once
#include <Arduino.h>

// Initialize authentication and retrieve JWT from storage or portal
void setupEdgeAuth();

// Triggers authentication handshake with the sovereign portal
void authenticateWithPortal();

// Get the cached JWT token
String getEdgeToken();
