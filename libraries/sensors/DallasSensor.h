#pragma once

#include <Arduino.h>
#include <DallasTemperature.h>
#include <string.h>

#include "Sensor.h"

class DallasBus;

class DallasSensor : public Sensor {
    public:
        DallasSensor(
            DallasBus& bus,
            const String& sensorName,
            const DeviceAddress& address
        );

        Measurement read() override;
    
    private:
        DallasBus& bus;
        DeviceAddress address;
        String sensorName;
};