# IoT Devices Roadmap

This document outlines the planned development of the IoT Devices firmware.

The roadmap evolves together with the project as new hardware and software features are implemented.

---

## Quick Links

📦 **IoT Devices Repository**

https://github.com/FD-technic/iot-devices

📦 **IoT Server Repository**

https://github.com/FD-technic/iot-server

---

# Current Status

## Completed

- ESP32 firmware
- HTTP communication
- JSON messaging
- Sensor abstraction
- Command processing
- PlatformIO project

The firmware provides a reusable foundation for ESP32-based IoT devices.

---

# Short-Term Goals

## Device Configuration

Support configurable devices.

Planned features

- device name
- polling interval
- enabled sensors
- calibration values

---

## Sensor Library

Extend supported sensors.

Planned support

- BME280
- DHT22
- BH1750
- Relay modules

---

# Mid-Term Goals

## OTA Updates

Support remote firmware updates.

---

## Power Optimization

Improve battery-powered deployments.

Planned improvements

- deep sleep
- wake-up scheduling
- power profiling

---

# Long-Term Goals

## MQTT Communication

Optional MQTT communication alongside REST.

---

## Smart Device Management

Future functionality

- automatic discovery
- firmware management
- diagnostics
- logging

---

# Long-Term Vision

IoT Devices aims to become a reusable firmware framework for ESP32-based IoT projects.

The project also serves as a portfolio application demonstrating:

- C++
- ESP32
- PlatformIO
- IoT communication
- Embedded programming
- Clean architecture
- Modular firmware design

---

Developed by **Petr Hron**

🌐 https://fdweb.cz

💼 https://linkedin.com/in/petr-hron-dev