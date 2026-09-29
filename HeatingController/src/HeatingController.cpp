#include "HeatingController.h"

void HeatingController::init()
{
    pinMode(pumpPin, OUTPUT);
    pinMode(valvePlusPin, OUTPUT);
    pinMode(valveMinusPin, OUTPUT);
    
    digitalWrite(pumpPin, HIGH);
    digitalWrite(valvePlusPin, HIGH);
    digitalWrite(valveMinusPin, HIGH);
}

void HeatingController::pumpHeating(bool run, PeripheralStatus& peripheralStatus) 
{
    peripheralStatus.heatingPump = run;
    digitalWrite( pumpPin, !run);
}

ValveDirection HeatingController::setDirection(const Temperatures& temperatures) 
{
    if ( (temperatures.local.inHeating - temperatures.target.heatingHysteresis) < temperatures.local.outHeating )
    {
        return ValveDirection::UP;
    }
    else if ( temperatures.local.inHeating >= temperatures.local.outHeating || (temperatures.local.inHeating + 35) > temperatures.target.room )
    {
        return ValveDirection::DOWN;
    }
    
    return ValveDirection::STOP;
}

int HeatingController::setValvePin(ValveDirection direction) 
{
    uint8_t valvePin = 0;

    if ( direction == ValveDirection::UP )
    {
        valvePin = Config::Pins::VALVE_PLUS;
    }
    else if ( direction == ValveDirection::DOWN )
    {
        valvePin = Config::Pins::VALVE_MINUS;
    }
    
    return valvePin;
}

void HeatingController::moveValve(int valvePin, bool valveRun, PeripheralStatus& peripheralStatus)
{
    if (valvePin == Config::Pins::VALVE_MINUS) {
        peripheralStatus.valveDirection = ValveDirection::DOWN;
    } else if (valvePin == Config::Pins::VALVE_PLUS) {
        peripheralStatus.valveDirection = ValveDirection::UP;
    } else {
        peripheralStatus.valveDirection = ValveDirection::STOP;
    }
    
    digitalWrite( valvePin, !valveRun);
}