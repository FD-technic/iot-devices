#include <Arduino.h>

#include <Wire.h>
#include <Network.h>
#include <DallasBus.h>
#include <DallasManager.h>

#include "Config.h"

Network network;

DallasBus bus(Config::Pins::DALLAS);
DallasManager manager(bus);

const int blinkLed = Config::Pins::BUILTIN_LED;

const int freq = 30;
const int cyclesBlink = 5;

const int sleeping = 10 * 60* 1000;

void blink();
void addMeasurements(MeasurementBatch& batch);

void setup()
{
    Serial.begin(115200);
    delay(200);

    if (!manager.init())
    {
        Serial.println("Dallas init failed");
    }

    manager.addSensor(Config::Device::TEMP);

    network.begin();

    //pinMode(blinkLed, OUTPUT);
}

void loop() {

    MeasurementBatch batch(Config::Device::DEVICE_NAME);

    addMeasurements(batch);

    ApiResponse response = network.sendBatch(batch);
    
    //blink();

    delay(sleeping);
}

// === Functions ===

void blink()
{
    for (int i = 0; i < cyclesBlink; i++)
    {
        digitalWrite(blinkLed, LOW);
        delay(freq);
        digitalWrite(blinkLed, HIGH);
        delay(freq * 3);
    }
}

void addMeasurements(MeasurementBatch& batch) {
    manager.addMeasurements(batch);
}
