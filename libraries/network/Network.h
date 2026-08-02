#pragma once

#include <WiFiService.h>
#include <ApiClient.h>

class Network
{
public:
    Network(
        const char* ssid,
        const char* password,
        const char* serverUrl);
    void begin();

    bool isConnected();

    ApiResponse send(const MeasurementBatch& batch);

private:
    WiFiService wifi;
    ApiClient api;
};