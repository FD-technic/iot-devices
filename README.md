# IoT Devices

IoT Devices is a firmware project for ESP32-based devices communicating with the IoT Server over HTTP.

The project provides reusable components for sensor integration, networking, JSON communication and command execution. It serves as a foundation for environmental monitoring and future IoT applications.

---

## Quick Links

📦 **IoT Devices Repository**

https://github.com/FD-technic/iot-devices

📦 **IoT Server Repository**

https://github.com/FD-technic/iot-server

---

# Hardware

### ESP32 Weather Station

![ESP32 Weather Station](docs/pic/esp32-weather.jpg)

---

### ESP32 Temperature Sensor

![ESP32 Temperature Sensor](docs/pic/esp32-temperature.jpg)

---

### IoT Server

The firmware communicates with the Spring Boot backend running on an Orange Pi.

![Orange Pi](docs/pic/orangepi.jpg)

---

# Communication

### Running IoT Server

The backend is deployed as a Linux systemd service.

![IoT Server Service](docs/pic/systemctl-status.png)

---

### Registered Devices

The firmware communicates with the backend through REST APIs.

![Registered Devices](docs/pic/postman-devices.png)

---

### Historical Sensor Data

Collected measurements are available through the backend API.

![Historical Data](docs/pic/postman-charts.png)

---

# Features

- ESP32 firmware
- HTTP communication
- JSON messaging
- Modular sensor architecture
- Automatic telemetry reporting
- Command execution
- PlatformIO support
- Reusable firmware components

---

# Tech Stack

- C++
- PlatformIO
- ESP32
- Arduino Framework
- ArduinoJson
- HTTP Client
- WiFi
- Git
- GitHub

---

# Architecture

```text
Sensors
    │
    ▼
Measurement Layer
    │
    ▼
JSON Payload
    │
    ▼
HTTP Client
    │
    ▼
IoT Server
    │
    ▼
JSON Commands
    │
    ▼
Device Actions
```

---

# Supported Hardware

- ESP32
- ESP32-C3
- DS18B20
- BMP280
- AHT20

---

# Getting Started

## Requirements

- PlatformIO
- ESP32 board package

---

## Build

```bash
pio run
```

---

## Upload

```bash
pio run --target upload
```

---

# Project Status

## Implemented

- HTTP communication
- JSON serialization
- Sensor abstraction
- Modular architecture
- Device commands

## Planned

- OTA firmware updates
- MQTT support
- Additional sensors
- Configuration management
- Deep sleep optimization

---

# Documentation

- architecture.md
- roadmap.md

---

# License

MIT