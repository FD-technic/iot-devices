#include "WaterHeaterController.h"


ServerResponse serverResponse;

void WaterHeaterController::init()
{
    pinMode(waterHeaterPin, OUTPUT);

    digitalWrite(waterHeaterPin, HIGH);
}

void WaterHeaterController::pumpPower(float heaterTemp, float inValve, int hysteresis, PeripheralStatus& peripheralStatus) 
{
    int waterHeaterTargetTemp = serverResponse.target.waterHeater;
    
    if ( heaterTemp < (inValve - hysteresis) )
    {
        pumpRun = true;
    }
    else if ( heaterTemp >= inValve || 
        heaterTemp > waterHeaterTargetTemp )
    {
        pumpRun = false;
    }

    peripheralStatus.waterHeaterPump = pumpRun;

    digitalWrite( waterHeaterPin, !pumpRun );
}

void WaterHeaterController::pumpPower(bool run, PeripheralStatus& peripheralStatus)
{
    peripheralStatus.waterHeaterPump = run;

    digitalWrite( waterHeaterPin, !run );
}