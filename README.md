# Sovereign-Edge-Firmware

**Coastal Alpine Tech Limited**
Firmware repository for ESP32 edge nodes operating within the Sovereign AI Stack. 

## Architecture
This firmware is designed to operate completely off-grid, utilizing local ES256 JWT authentication via the Blue-Moon-Portal, communicating over mTLS-secured MQTT.

## SecOps Notice
Never commit `secrets.h` to this repository. All physical node configurations must remain local to the deployment site.
