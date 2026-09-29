#include "Config.h"

#include <Arduino.h>

#include <Network.h>
#include <DallasBus.h>
#include <DallasManager.h>
#include "TemperatureManager.h"
#include "WaterHeaterController.h"
#include "HeatingController.h"

/*
 === INITIAL ===
*/
Network network;

DallasBus bus(Config::Pins::DALLAS);
DallasManager dallasManager(bus);

TemperatureManager temperatureManager;
WaterHeaterController waterHeaterController;
HeatingController heatingController;
PeripheralStatus peripheralStatus;


/*
 === CONSTAMTS ===
*/
unsigned long lastMeasurementTime = 0;
unsigned long lastStatusTime = 0;
unsigned long valveStartTime = 0;
// const unsigned long periodTimer = 5000; // dev 2s
const unsigned long periodTimer = 20000; // production 20s
const unsigned long manualModeTimer = 1000;
unsigned long timer = periodTimer;
const unsigned long valveRunTime = 2000;

bool heatingPumpRun = false;
bool valveRun = false;
int valveMoving = 0;

HeatingMode heatingMode = HeatingMode::DAY;

void runManualMode(ApiResponse response);
void runAutoMode(const Temperatures& temperatures);
void valveStop();

/*
 === PROGRAM ===
*/
void setup()
{
    Serial.begin(115200);
    delay(200);

    if (!dallasManager.init())
    {
        Serial.println("Dallas init failed");
    }

    dallasManager.addSensor("inHeating", Config::SensorsAddress::IN_HEATING);
    dallasManager.addSensor("outHeating", Config::SensorsAddress::OUT_HEATING);
    dallasManager.addSensor("inValve", Config::SensorsAddress::IN_VALVE);
    dallasManager.addSensor("waterHeater", Config::SensorsAddress::WATER_HEATER);

    peripheralStatus.deviceName = Config::Device::DEVICE_NAME;

    network.begin();

    heatingController.init();
    waterHeaterController.init();

    lastMeasurementTime = millis();
}

void loop()
{

    timer = heatingMode == HeatingMode::MANUAL ? manualModeTimer : periodTimer;

    if ((millis() - lastStatusTime) >= 1000) {
        lastStatusTime = millis();
        network.sendStatus(peripheralStatus);
    }
    if ((millis() - lastMeasurementTime) >= timer)
    {
        lastMeasurementTime = millis();

        MeasurementBatch batch(peripheralStatus.deviceName);

        dallasManager.addMeasurements(batch);

        ApiResponse response = network.sendBatch(batch);
        
        heatingMode = response.data.heatingMode;
        
        temperatureManager.updateLocal(batch);
        
        temperatureManager.updateRemote(response.data);
        
        const auto &temperatures = temperatureManager.getTemperatures();
        
        peripheralStatus.heatingMode = heatingMode;
        
        if (heatingMode == HeatingMode::OFF)
        {
            valveStop();
            heatingController.pumpHeating(false, peripheralStatus);
            waterHeaterController.pumpPower(false, peripheralStatus);
            return;
        }
        else if (heatingMode == HeatingMode::MANUAL)
        {
            runManualMode(response);
        }
        else
        {
            runAutoMode(temperatures);
        }

        if (
            (((millis() - valveStartTime) >= valveRunTime) && valveRun))
        {
            valveStop();
        }
    }
}


/*
 === FUNCTIONS ===
*/
void runAutoMode(const Temperatures& temperatures) {
    heatingPumpRun = 
        heatingMode == HeatingMode::DAY || 
        heatingMode == HeatingMode::NIGHT;
    
    heatingController.pumpHeating(heatingPumpRun, peripheralStatus);
    
    if (valveMoving == 0)
    {
        valveMoving = heatingController.setValvePin(heatingController.setDirection(temperatures));
    } 
    
    if (valveMoving != 0 && !valveRun)
    {
        valveStartTime = millis();
        valveRun = true;
        heatingController.moveValve(valveMoving, valveRun, peripheralStatus);
    }
    
    waterHeaterController.pumpPower(
        temperatures.local.waterHeater,
        temperatures.local.inValve,
        temperatures.target.waterHeatingHysteresis,
        peripheralStatus
    );
}

void runManualMode(ApiResponse response) {
    heatingController.pumpHeating(response.data.manual.heatingPump, peripheralStatus); 
    waterHeaterController.pumpPower(response.data.manual.waterHeaterPump, peripheralStatus);  
    if( response.data.manual.valveDirection != ValveDirection::STOP && !valveRun) 
    {
        valveMoving = heatingController.setValvePin(response.data.manual.valveDirection);
        valveStartTime = millis();
        valveRun = true;
        heatingController.moveValve(valveMoving, valveRun, peripheralStatus); 
    }
}

void valveStop() {
    valveRun = false;
    valveMoving = 0;
    heatingController.moveValve(valveMoving, valveRun, peripheralStatus);
}
