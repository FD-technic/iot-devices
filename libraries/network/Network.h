#pragma once

#include <WiFiService.h>
#include "ApiClient.h"
#include "HeatingConfig.h"

class Network
{
public:
    Network();
    void begin();

    bool isConnected();

    ApiResponse sendBatch(const MeasurementBatch& batch);
    void sendStatus(const PeripheralStatus& status);

private:
    WiFiService wifi;
    ApiClient api;
};