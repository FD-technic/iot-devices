#pragma once

#include <Arduino.h>

#include <vector>
#include "DallasBus.h"
#include "DallasSensor.h"
#include "dto/MeasurementBatch.h"

class DallasManager
{
public:
    DallasManager(DallasBus& bus);

    void addSensor(
        const char* name);

    
    void addSensor(
        const char* name,
        const DeviceAddress& address
    );

    bool init();

    void addMeasurements(MeasurementBatch& batch);

private:
    DallasBus& bus;
    std::vector<DallasSensor> sensors;
};