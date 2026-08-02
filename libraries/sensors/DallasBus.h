#pragma once

#include <Arduino.h>

#include <OneWire.h>

#include "DallasSensor.h"

class DallasBus {
    public:
        explicit DallasBus(uint8_t pin);

        bool init();
        int getCount();
        
        void requestTemperatures();
        bool getFirstAddress(DeviceAddress& address);
        double getTemperature(const DeviceAddress& address);
        double getTemperature();
    
    private:
        OneWire oneWire;
        DallasTemperature sensors;
};
