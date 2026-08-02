#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include "enums/DeviceType.h"
#include "dto/apiResponse.h"
#include "dto/MeasurementBatch.h"
#include "dto/Device.h"

class ApiClient {
    public:
        explicit ApiClient(const char* serverUrl);

        ApiResponse createDevice(const Device& device);
        ApiResponse sendMeasurements(const MeasurementBatch& batch);
        
    private:
        const char* serverUrl;
        static constexpr const char* DEVICE_ENDPOINT = "/api/devices";
        static constexpr const char* MEASUREMENT_ENDPOINT = "/api/measurements";

        ApiResponse post(
            const char* endpoint,
            const JsonDocument& doc);

        ApiResponse parseResponse(
            int httpCode,
            const String& response);
};