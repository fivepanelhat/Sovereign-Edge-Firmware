# Sovereign-Edge-Firmware - install notes

**Coastal Alpine Tech Limited** (pre-seed). This repo is **ESP32 / Arduino firmware**, not a Python package.

## Cross-platform setup

| Host | Tooling |
| :--- | :--- |
| Windows | Arduino IDE 2.x **or** [arduino-cli](https://arduino.github.io/arduino-cli/) |
| Linux / macOS | Same |

### arduino-cli (recommended)

```bash
# Install arduino-cli for your OS, then:
arduino-cli core update-index
arduino-cli core install esp32:esp32
arduino-cli lib install "PubSubClient"
# open / compile sketches under examples/ or src/ as documented in README
```

### Hub side (Pi)

Field nodes talk mTLS MQTT into a **Raspberry Pi 5 16GB** hub. Install the hub stack via:

- [Coastal-Alpine-Core](https://github.com/fivepanelhat/Coastal-Alpine-Core) `install.sh` / `install.ps1`
- or [coastal-alpine-stack](https://github.com/fivepanelhat/coastal-alpine-stack)

There is no `pip install` for this firmware repo by design.
