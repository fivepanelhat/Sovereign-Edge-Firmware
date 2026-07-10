# Sovereign Edge Firmware

**Coastal Alpine Tech Limited**

[![License](https://img.shields.io/badge/License-Proprietary--Commercial-blue?style=flat-square)](LICENSE)  
[![Platform](https://img.shields.io/badge/Platform-ESP32%20%2B%20RPi%205-blue?style=flat-square)]()  
[![Hardware Target](https://img.shields.io/badge/Hardware-Raspberry%20Pi%205%2016GB-C11A5B?style=flat-square&logo=raspberry-pi&logoColor=white)]()  
[![NPU Acceleration](https://img.shields.io/badge/NPU-Hailo--10H%20Accelerated-005A9C?style=flat-square)]()  
[![Sovereignty](https://img.shields.io/badge/Sovereignty-NZ%20Data%20Bound-00247D?style=flat-square)]()  
[![CI](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/ci-scan.yml/badge.svg?branch=master)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/ci-scan.yml)  
[![SecOps Scan](https://img.shields.io/github/actions/workflow/status/fivepanelhat/Sovereign-Edge-Firmware/secops.yml?branch=master&label=SecOps%20Scan&style=flat-square&color=success)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/secops.yml)  
[![RedTeam](https://img.shields.io/github/actions/workflow/status/fivepanelhat/Sovereign-Edge-Firmware/redteam.yml?branch=master&label=RedTeam&style=flat-square&color=critical)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/redteam.yml)  
[![Dependabot](https://img.shields.io/badge/Dependencies-Monitored-brightgreen?style=flat-square&logo=dependabot)]()  
[![Interop](https://img.shields.io/badge/Interop-MQTT%20%7C%20OPC--UA-orange?style=flat-square)]()  
[![Sustainability](https://img.shields.io/badge/EECA%20NZ-Carbon%20Tracked-green?style=flat-square)]()

Firmware repository for ESP32 edge nodes operating within the Sovereign AI Stack. 

## Architecture
This firmware is designed to operate completely off-grid, utilizing local ES256 JWT authentication via the Blue-Moon-Portal, communicating over mTLS-secured MQTT.

## SecOps Notice
Never commit `secrets.h` to this repository. All physical node configurations must remain local to the deployment site.

---

## Garden Sensor Node (Arduino IDE Build)

A local, decentralized IoT sensor network for monitoring garden environmental metrics. This node publishes data to a Raspberry Pi 5 via MQTT, processed by Node-RED, and stored in InfluxDB 2 for local data sovereignty.

> **Note:** The PlatformIO build system (see `platformio.ini`) is used for the mTLS production firmware above. The Garden Sensor Node documented below uses **Arduino IDE (v1.8.19)** for rapid prototyping with the DHT11 and rain sensor. Both target the same ESP32 hardware.

### Hardware

| Component | Model & Details |
| --- | --- |
| **Microcontroller** | Keyestudio ESP32 (XC3800) |
| **Local Server** | Raspberry Pi 5 **16GB** (arm64) + AI HAT+ 2 (**Hailo-10H**, 40 TOPS) |
| **Temp/Humidity** | DHT11 (XC4520) |
| **Rain Sensor** | Duinotech Rain Sensor (XC4603) |

### Software & Infrastructure

* **OS:** Raspberry Pi OS / Debian Trixie
* **Firmware:** Arduino IDE (v1.8.19), ESP32 Core
* **Broker:** Mosquitto MQTT (v2.0.21-1)
* **Database:** InfluxDB 2 (v2.9.1-1)
* **Integration:** Node-RED (v5.0.0)

### Wiring Reference

| Sensor | Module Pin | ESP32 Pin | Notes |
| --- | --- | --- | --- |
| **DHT11** | S | GPIO4 | Ensure empty rows between pins to prevent shorts |
| **DHT11** | V | 5V | Direct to ESP32 currently |
| **DHT11** | G | GND | Direct to ESP32 currently |
| **Rain Sensor** | VCC | 5V Rail | Powered from shared breadboard rail |
| **Rain Sensor** | GND | GND Rail | Grounded to shared breadboard rail |
| **Rain Sensor** | AO | GPIO34 | ADC-capable input |
| **Rain Sensor** | DO | N/A | Unconnected |

> **⚠️ Warning:** Be incredibly careful with DHT11 pin placement. Placing S, V, and G in the same breadboard row will short the power to ground, causing a Pi 5 USB over-current event and knocking peripherals offline.

### Known Issues & Troubleshooting

* **Wi-Fi Connection Loops:** ESP32 SSIDs are strictly case-sensitive. Ensure your capitalization is perfectly matched.
* **Failed ESP32 Uploads:** The Pi 5 and ESP32 USB-to-UART combination can repeatedly drop out at high speeds. Hardcode your Arduino IDE upload speed to **115200 baud** to maintain stability.
* **Busy Serial Port:** If an upload fails, the IDE's Java process will often hold `/dev/ttyUSB0` hostage. Closing the Serial Monitor usually releases the lock.
* **Compiler/Linker Errors:** Repeated USB upload interruptions can eventually corrupt the ESP32 board package files (throwing EOF or getApbFrequency errors). Resolve this by deleting `~/.arduino15/packages/esp32` and reinstalling via the Boards Manager.

### Project Roadmap

* Confirm fresh ESP32 board package reinstall completes and compiling succeeds.
* Re-upload the combined sketch (DHT11 + rain sensor + MQTT) with a healthy compiler.
* Debug intermittent DHT11 reads (test migrating power from direct-ESP32 to the shared 5V rail).
* Complete Node-RED wiring for `garden/sensor1/rain` directly to InfluxDB.
* Integrate physical light and moisture sensors into the enclosure.
* Deploy Grafana to visualize the InfluxDB metrics.
* Configure persistent headless boot for all Pi services (`systemctl enable`).

---

For the full consolidated setup guide, see [garden-sensor-network-setup.md](../docs/garden-sensor-network-setup.md).

Wayne Roberts, Coastal Alpine Tech Limited

## License

Proprietary — Coastal Alpine Tech Limited. See [LICENSE](./LICENSE).
