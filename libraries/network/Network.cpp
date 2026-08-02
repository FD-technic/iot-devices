#include "Network.h"

Network::Network(
    const char* ssid,
    const char* password,
    const char* serverUrl)
    : wifi(ssid, password),
    api(serverUrl)
{
}

void Network::begin()
{
    wifi.connect();
}

bool Network::isConnected()
{
    return wifi.isConnected();
}

ApiResponse Network::send(const MeasurementBatch& batch)
{
    if (!wifi.isConnected())
        wifi.connect();

    return api.sendMeasurements(batch);
}
