#pragma once
#include <Arduino.h>

void setupMQTT();
void connectToWeaver();
void publishSensorData(float soilMoisture);
