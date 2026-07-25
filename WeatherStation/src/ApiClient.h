#pragma once

#include <Arduino.h>
#include "enums/DeviceType.h"
#include "dto/apiResponse.h"


struct IrrigationPayload {
    double mainTemperature;
    double inputTemperature;
    double outputTemperature;
};

struct TemperaturePayload {
    double value;
    String deviceName;
};

class ApiClient {
    public:
        ApiResponse sendMessage(const IrrigationPayload& payload, DeviceType type);
        ApiResponse sendTemperature(const TemperaturePayload& payload);
        ApiResponse createDevice(String type);
};