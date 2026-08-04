# IoT Devices Architecture

## Project Overview

IoT Devices is a modular ESP32 firmware project designed for communication with the IoT Server.

The firmware periodically collects sensor data, sends telemetry over HTTP and executes commands received from the server.

---

## Quick Links

📦 **IoT Devices Repository**

https://github.com/FD-technic/iot-devices

📦 **IoT Server Repository**

https://github.com/FD-technic/iot-server

---

# System Architecture

```text
Sensors
    │
    ▼
Measurement Layer
    │
    ▼
Device Model
    │
    ▼
JSON Serialization
    │
    ▼
HTTP Client
    │
    ▼
IoT Server
```

---

# Project Structure

```text
src
│
├── sensors
├── network
├── api
├── model
├── config
└── main.cpp
```

---

# Application Layers

| Layer | Responsibility |
|--------|----------------|
| sensors | Reading physical sensors |
| network | WiFi connection |
| api | HTTP communication |
| model | Shared data models |
| config | Device configuration |
| main | Application lifecycle |

---

# Communication Flow

1. Sensors collect measurements.
2. Measurements are converted into a device model.
3. The model is serialized into JSON.
4. The firmware sends data to the IoT Server.
5. The server returns commands.
6. The firmware executes received commands.

---

# Design Principles

- Modular architecture
- Sensor abstraction
- JSON communication
- HTTP protocol
- Reusable components
- Easy sensor integration

---

Developed by **Petr Hron**

🌐 https://fdweb.cz

💼 https://linkedin.com/in/petr-hron-dev