#include "Network.h"

Network::Network()
    : wifi(
        HeatingConfig::WiFi::SSID,
        HeatingConfig::WiFi::PASSWORD
    ),
    api(
        HeatingConfig::Api::SERVER_URL
    )
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

ApiResponse Network::sendBatch(const MeasurementBatch& batch)
{
    if (!wifi.isConnected())
        wifi.connect();

    return api.sendMeasurements(batch);
}

void Network::sendStatus(const PeripheralStatus& status)
{
    if (!wifi.isConnected())
        wifi.connect();

    api.sendPeripheralStatus(status);
}
