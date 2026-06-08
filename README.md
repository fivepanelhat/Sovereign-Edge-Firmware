# Sovereign-Edge-Firmware

[![License](https://img.shields.io/badge/License-Proprietary--Commercial-blue?style=flat-square)](LICENSE)  
[![Sovereignty](https://img.shields.io/badge/Sovereignty-NZ%20Data%20Bound-00247D?style=flat-square)]()  
[![Interop](https://img.shields.io/badge/Interop-MQTT%20%7C%20OPC--UA-orange?style=flat-square)]()

**Coastal Alpine Tech Limited**
Firmware repository for ESP32 edge nodes operating within the Sovereign AI Stack. 

## Architecture
This firmware is designed to operate completely off-grid, utilizing local ES256 JWT authentication via the Blue-Moon-Portal, communicating over mTLS-secured MQTT.

## SecOps Notice
Never commit `secrets.h` to this repository. All physical node configurations must remain local to the deployment site.
