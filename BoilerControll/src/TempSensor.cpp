#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Config.h"
#include "TempSensor.h"

constexpr uint8_t DALLAS_PIN = 26;

// OneWire sběrnice
OneWire oneWire(DALLAS_PIN);

// Dallas knihovna
DallasTemperature sensors(&oneWire);

void TempSensor::init()
{
    Serial.println();
    Serial.println("Initializing Dallas sensor...");

    sensors.begin();

    Serial.print("Sensors found: ");
    Serial.println(sensors.getDeviceCount());
}

double TempSensor::read() {
  sensors.requestTemperatures();

    double temperature = sensors.getTempCByIndex(0);

    if (temperature == DEVICE_DISCONNECTED_C)
    {
        Serial.println("Dallas sensor not connected!");
    }
    
    return temperature;
}
