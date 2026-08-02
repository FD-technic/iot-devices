#include "DallasManager.h"

#include "DallasBus.h"

DallasManager::DallasManager(DallasBus& bus)
    : bus(bus)
{

}

bool DallasManager::init()
{
    return bus.init();
}

void DallasManager::addSensor(const char *name)
{
    DeviceAddress address;

    if (!bus.getFirstAddress(address))
    {
        Serial.println("No Dallas sensor found!");
        return;
    }

    sensors.emplace_back(bus, name, address);
}

void DallasManager::addSensor(const char *name, const DeviceAddress& address)
{
    sensors.emplace_back(bus, name, address);
}

void DallasManager::addMeasurements(MeasurementBatch &batch)
{
    bus.requestTemperatures();

    for (auto& sensor : sensors) {
        batch.measurements.push_back(sensor.read());
    }
}
