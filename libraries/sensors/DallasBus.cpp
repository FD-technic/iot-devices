#include "DallasBus.h"

DallasBus::DallasBus(uint8_t pin) 
    : oneWire(pin),
    sensors(&oneWire)
{

}

bool DallasBus::init()
{
    Serial.println();
    Serial.println("Initializing Dallas sensor...");

    sensors.begin();

    Serial.print("Sensors found: ");
    Serial.println(sensors.getDeviceCount());

    return true;
}

int DallasBus::getCount() {
    return sensors.getDeviceCount();
}

bool DallasBus::getFirstAddress(DeviceAddress& address)
{
    return sensors.getAddress(address, 0);
}

void DallasBus::requestTemperatures()
{
    sensors.requestTemperatures();
}

double DallasBus::getTemperature(const DeviceAddress& address)
{
    return sensors.getTempC(address);
}

double DallasBus::getTemperature()
{
    return sensors.getTempCByIndex(0);
}