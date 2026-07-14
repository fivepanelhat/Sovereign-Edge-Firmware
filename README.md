# Sovereign Edge Firmware

[![License: Proprietary](https://img.shields.io/badge/License-Proprietary--Commercial-blue.svg)](./LICENSE)
[![Platform](https://img.shields.io/badge/Platform-ESP32%20%2B%20RPi%205-0078D6)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware)
[![Arduino](https://img.shields.io/badge/Build-Arduino%20%7C%20PlatformIO-00979D?logo=platformio&logoColor=white)](https://platformio.org)

[![Linux](https://img.shields.io/badge/Linux-Ubuntu%2C%20Debian%2C%20Fedora-FCC624?logo=linux&logoColor=black)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware)
[![Windows](https://img.shields.io/badge/Windows-10%2B-0078D4?logo=windows&logoColor=white)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware)
[![macOS](https://img.shields.io/badge/macOS-12%2B-000000?logo=apple&logoColor=white)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware)
[![Raspberry Pi](https://img.shields.io/badge/Raspberry%20Pi-5%20%2816GB%29-C11A5B?logo=raspberry-pi&logoColor=white)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware)

[![Claude AI](https://img.shields.io/badge/Claude-Anthropic-9C27B0)](https://anthropic.com)
[![Gemini](https://img.shields.io/badge/Gemini-Google-4285F4?logo=google&logoColor=white)](https://gemini.google.com)
[![OpenAI](https://img.shields.io/badge/OpenAI-GPT--4-00A67E)](https://openai.com)
[![Grok](https://img.shields.io/badge/Grok-xAI-000000)](https://x.ai)

[![Hailo NPU](https://img.shields.io/badge/NPU-Hailo--10H-005A9C)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware)
[![MQTT](https://img.shields.io/badge/MQTT-Mosquitto%20mTLS-3C5280?logo=mqtt&logoColor=white)](https://mosquitto.org)
[![Data Sovereign](https://img.shields.io/badge/Data%20Sovereign-NZ%20Bound-00247D)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware)

[![CI Status](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/ci-scan.yml/badge.svg?branch=master)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/ci-scan.yml)
[![SecOps](https://img.shields.io/github/actions/workflow/status/fivepanelhat/Sovereign-Edge-Firmware/secops.yml?branch=master&label=SecOps&color=success)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/secops.yml)
[![RedTeam](https://img.shields.io/github/actions/workflow/status/fivepanelhat/Sovereign-Edge-Firmware/redteam.yml?branch=master&label=RedTeam&color=critical)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/actions/workflows/redteam.yml)
[![Dependencies](https://img.shields.io/badge/Dependencies-Monitored-brightgreen?logo=dependabot)](https://github.com/fivepanelhat/Sovereign-Edge-Firmware/security/dependabot)

![Banner](assets/social_preview.png)


**Coastal Alpine Tech Limited** — pre-seed startup, New Plymouth, Taranaki, Aotearoa New Zealand.


Firmware repository for ESP32 edge nodes operating within the Sovereign AI Stack. 

## Architecture Overview

> **Diagrams:** Architecture images and Mermaid maps describe the **target product architecture** for this pre-seed stack. They are engineering design maps — not claims of large-scale commercial fleet deployment.

Field nodes run on **ESP32** with mTLS MQTT into a **Raspberry Pi 5 16GB** hub (AI HAT+ 2 / Hailo-10H capable). Sensor data stays on the local sovereign network.

![Sovereign Edge Firmware architecture — liquid glass overview](assets/architecture_overview.png)

### System map

```mermaid
%%{init: {
  "theme": "dark",
  "themeVariables": {
    "fontSize": "16px",
    "fontFamily": "Inter, ui-sans-serif, system-ui, sans-serif",
    "primaryColor": "#0ea5e9",
    "primaryTextColor": "#f8fafc",
    "primaryBorderColor": "#38bdf8",
    "lineColor": "#67e8f9",
    "secondaryColor": "#1e293b",
    "tertiaryColor": "#0f172a",
    "clusterBkg": "#0b1220cc",
    "clusterBorder": "#38bdf880",
    "titleColor": "#e2e8f0"
  },
  "flowchart": {
    "nodeSpacing": 40,
    "rankSpacing": 48,
    "padding": 20,
    "htmlLabels": true,
    "curve": "basis"
  }
}}%%
flowchart LR

    classDef sense fill:#052e16,stroke:#4ade80,stroke-width:2px,color:#f0fdf4
    classDef edge fill:#0c4a6e,stroke:#38bdf8,stroke-width:2px,color:#f0f9ff
    classDef core fill:#134e4a,stroke:#2dd4bf,stroke-width:2px,color:#f0fdfa
    classDef act fill:#422006,stroke:#fbbf24,stroke-width:2px,color:#fffbeb
    classDef store fill:#1e1b4b,stroke:#a5b4fc,stroke-width:2px,color:#eef2ff
    classDef ai fill:#3b0764,stroke:#e879f9,stroke-width:2px,color:#fdf4ff
    classDef app fill:#1e1b4b,stroke:#c4b5fd,stroke-width:2px,color:#eef2ff

    S["Sensors<br/>DHT · rain · probes"] --> ESP["ESP32 firmware<br/>mTLS · JWT"]
    ESP --> MQTT["Mosquitto broker"]
    MQTT --> PI["RPi 5 16GB hub<br/>Node-RED · InfluxDB"]
    PI --> PORTAL["Portals / Weaver<br/>optional consumers"]

    class S sense
    class ESP act
    class MQTT,PI edge
    class PORTAL core
```

| Layer | Components | Role |
| :--- | :--- | :--- |
| **Node** | ESP32 + sensors | Field capture |
| **Security** | mTLS + local JWT | No open MQTT |
| **Hub** | RPi 5 16GB | Broker · DB · UI |
| **Consumers** | Portals / Weaver | Edge AI stack |

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

For the full consolidated setup guide, see `garden-sensor-network-setup.md` (not yet published — the previous link pointed to a non-existent path).

Wayne Roberts, Coastal Alpine Tech Limited

## License

Proprietary — Coastal Alpine Tech Limited. See [LICENSE](./LICENSE).
