#include <Arduino.h>

#include <Wire.h>
#include <Network.h>
#include <DallasBus.h>
#include <DallasManager.h>
#include <AHT20Sensor.h>
#include <Bmp280Sensor.h>

#include "Config.h"

Network network;

DallasBus bus(Config::Pins::DALLAS);
DallasManager manager(bus);
AHT20Sensor humidity("Humidity");
Bmp280Sensor pressure("Pressure");

const int blinkLed = Config::Pins::BUILTIN_LED;

const int freq = 30;
const int cyclesBlink = 5;

const int sleeping = 10 * 60 * 1000;
const uint64_t sleepTime = 10 * 60 * 1000000ULL;

void blink();
void addMeasurements(MeasurementBatch& batch);
void addTestMeasurements(MeasurementBatch& batch);

void setup()
{
    Serial.begin(115200);
    delay(200);

    Wire.begin(
        Config::Pins::I2C_SDA,
        Config::Pins::I2C_SCL);

    if (!manager.init())
    {
        Serial.println("Dallas init failed");
    }

    if (!humidity.init())
    {
        Serial.println("AHT20 not found");
    }

    if (!pressure.init())
    {
        Serial.println("BMP280 not found");
    }
    delay(200);

    manager.addSensor("Temperature");

    network.begin();

    //pinMode(blinkLed, OUTPUT);
}

void loop() {

    MeasurementBatch batch(Config::Device::DEVICE_NAME);

    addMeasurements(batch);
    //addTestMeasurements(batch);

    ApiResponse response = network.sendBatch(batch);
    
    //blink();

    // delay(sleeping);

    Serial.println("Usinam...");

    esp_sleep_enable_timer_wakeup(sleepTime);
    esp_deep_sleep_start();
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
    
    batch.add(humidity.read());
    batch.add(pressure.read());
}

void addTestMeasurements(MeasurementBatch& batch)
{
    batch.add({"Temperature", MeasurementType::TEMPERATURE, 23.4});
    batch.add({"Humidity", MeasurementType::HUMIDITY, 58.7});
    batch.add({"Pressure", MeasurementType::PRESSURE, 1013.2});
}

void addFakeMeasurements(MeasurementBatch& batch)
{
    batch.add({"Temperature", MeasurementType::TEMPERATURE, 23.4});
    batch.add({"Humidity", MeasurementType::HUMIDITY, 58.7});
    batch.add({"Pressure", MeasurementType::PRESSURE, 1013.2});
    batch.add({"rssi", MeasurementType::RSSI, -61});
    batch.add({"uptime", MeasurementType::UPTIME, millis() / 1000});
}