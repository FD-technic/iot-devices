#include "DallasSensor.h"
#include "DallasBus.h"
#include "../core/enums/MeasurementType.h"

DallasSensor::DallasSensor(
    DallasBus& bus,
    const String& sensorName,
    const DeviceAddress& address)
    : bus(bus),
      sensorName(sensorName)
{
    memcpy(this->address, address, sizeof(DeviceAddress));
}

Measurement DallasSensor::read() {
    return {
        sensorName,
        MeasurementType::TEMPERATURE,
        bus.getTemperature(address)
    };
}
