#ifndef HEATING_CONTROLLER_H
#define HEATING_CONTROLLER_H

#include "TemperatureManager.h"
#include <Config.h>
#include "enums/Heating.h"
#include "dto/apiResponse.h"

class HeatingController
{
    public:
        void init();
        void pumpHeating(bool pumpRun, PeripheralStatus& peripheralStatus);
        ValveDirection setDirection(const Temperatures& temperatures);
        int  setValvePin(ValveDirection direction);
        void moveValve(int valveDirection, bool valveRun, PeripheralStatus& peripheralStatus);

    private:
        const int pumpPin = Config::Pins::PUMP;
        const int valvePlusPin = Config::Pins::VALVE_PLUS;
        const int valveMinusPin = Config::Pins::VALVE_MINUS;
};

#endif