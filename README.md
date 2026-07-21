# Sovereign Edge Firmware

[![Privacy](https://img.shields.io/badge/Privacy-Local--first%20%2B%20Privacy%20Act%202020-00247D)](./COMPLIANCE.md)
[![No data sold](https://img.shields.io/badge/Data-Not%20sold%20to%20third%20parties-0f766e)](./COMPLIANCE.md)
[![NZ Privacy Act](https://img.shields.io/badge/NZ-Privacy%20Act%202020-00247D)](./COMPLIANCE.md)
[![Te Mana Raraunga](https://img.shields.io/badge/Te%20Mana%20Raraunga-In%20accordance-0f766e)](./COMPLIANCE.md)
[![NZ AI Safety](https://img.shields.io/badge/NZ%20AI%20Safety-Aligned-8B5CF6)](./COMPLIANCE.md)
[![SOC2](https://img.shields.io/badge/SOC%202-Alignment%20path-6366f1)](./COMPLIANCE_REGIONS.md)
[![Regions](https://img.shields.io/badge/AU%20%7C%20Asia%20%7C%20EU-Mapped-0ea5e9)](./COMPLIANCE_REGIONS.md)
[![Security](https://img.shields.io/badge/Security-No%20silent%20exfil%20%2B%20SecOps-dc2626)](./SECURITY.md)
[![Governance](https://img.shields.io/badge/Governance-HITL%20%2B%20Te%20Mana%20Raraunga-0f766e)](./COMPLIANCE.md)


![CI](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/secops.yml/badge.svg?branch=main)

![Hardware Target](https://img.shields.io/badge/Hardware-Raspberry%20Pi%205%2016GB-C11A5B?style=flat-square&logo=raspberry-pi&logoColor=white) ![NPU Acceleration](https://img.shields.io/badge/NPU-Hailo--10H%20Accelerated-005A9C?style=flat-square) ![Protocols](https://img.shields.io/badge/Interop-MQTT%20%7C%20OPC--UA-orange?style=flat-square)

**Coastal Alpine Tech Limited**
Firmware repository for ESP32 edge nodes operating within the Sovereign AI Stack. 

## Architecture
This firmware is designed to operate completely off-grid, utilizing local ES256 JWT authentication via the Blue-Moon-Portal, communicating over mTLS-secured MQTT.

## SecOps Notice
Never commit `secrets.h` to this repository. All physical node configurations must remain local to the deployment site.


<!-- BEGIN PRIVACY_SECURITY_GOVERNANCE -->
## Privacy / Security / Governance

Coastal Alpine Tech products treat operational and personal data as **taonga**. Defaults favour **local-first** operation, **purpose-limited** collection, and **Human-in-the-Loop** for high-stakes actions.

### Hard commitments

| Commitment | Statement |
| :--- | :--- |
| **No data sales** | **We do not sell personal information or customer operational data to third parties** for advertising, brokerage, or unrelated commercial exploitation. |
| **NZ Privacy Act 2020** | Collection, use, storage, and disclosure of personal information is designed to operate in accordance with the **Privacy Act 2020** information privacy principles (including IPP awareness and IPP 3A indirect-collection notification where applicable). |
| **Te Mana Raraunga** | Where Māori data or community data interests arise, systems are designed to operate **in accordance with Te Mana Raraunga** principles (including Rangatiratanga, Whakapapa, Whanaungatanga, Kotahitanga, Manaakitanga, Kaitiakitanga) as a sovereignty and stewardship lens — not as a marketing slogan. |
| **NZ AI safety** | AI features follow a **NZ AI safety-aligned** posture: Algorithm Charter spirit (fairness, transparency, human oversight where relevant), digital.govt.nz / responsible AI guidance awareness, no silent model training on private journals without consent, and HITL for high-stakes outcomes. |
| **Security** | No silent exfiltration; owner-controlled credentials; least privilege; SecOps / dependency hygiene on the fleet cadence. |
| **Governance** | Agents **inform, draft, prepare**; humans **advise, sign, file, send, and pay**. |

| Pillar | Commitment |
| :--- | :--- |
| **Privacy** | Local-first / offline-capable where practical; Privacy Act 2020; Te Mana Raraunga spirit; third-party AI only when **opt-in and labelled** |
| **Security** | No silent exfil of tenant or personal data; owner-controlled keys |
| **Governance** | HITL for high-stakes; Te Mana Raraunga spirit; multi-region compliance maps in [`COMPLIANCE_REGIONS.md`](./COMPLIANCE_REGIONS.md) |

**Agents inform, draft, prepare, monitor, and remind. Humans advise, sign, file, send, and pay.**

Fleet policy: [fivepanelhat / Kiwi Edge AI Stack](https://github.com/fivepanelhat/fivepanelhat) · [`COMPLIANCE.md`](./COMPLIANCE.md) · [`COMPLIANCE_REGIONS.md`](./COMPLIANCE_REGIONS.md) · [`SECURITY.md`](./SECURITY.md)
<!-- END PRIVACY_SECURITY_GOVERNANCE -->

---
## Garden Sensor Node (Arduino IDE Build)

A local, decentralized IoT sensor network for monitoring garden environmental metrics. This node publishes data to a Raspberry Pi 5 via MQTT, processed by Node-RED, and stored in InfluxDB 2 for local data sovereignty.

> **Note:** The PlatformIO build system (see `platformio.ini`) is used for the mTLS production firmware above. The Garden Sensor Node documented below uses **Arduino IDE (v1.8.19)** for rapid prototyping with the DHT11 and rain sensor. Both target the same ESP32 hardware.

### Hardware

| Component | Model & Details |
| --- | --- |
| **Microcontroller** | Keyestudio ESP32 (XC3800) |
| **Local Server** | Raspberry Pi 5 (arm64) + AI HAT 2+ |
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
