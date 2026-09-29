#ifndef WATER_HEATER_CONTROLLER_H
#define WATER_HEATER_CONTROLLER_H

#include <Config.h>
#include "TemperatureManager.h"
#include "dto/ServerResponse.h"
#include "dto/apiResponse.h"

class WaterHeaterController{
    public:
        void init();
        void pumpPower(float heaterTemp, float inValve, int hysteresis, PeripheralStatus& peripheralStatus);
        void pumpPower(bool run, PeripheralStatus& peripheralStatus);

    private:
        const int waterHeaterPin = Config::Pins::WATER_HEATER_PUMP;
        bool pumpRun = false;
};

#endif