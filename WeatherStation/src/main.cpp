#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Config.h"
#include "WifiService.h"
#include "ApiClient.h"
#include "TempSensor.h"
#include "./enums/DeviceType.h"

WifiService wifi;
ApiClient client;
TempSensor temp;

const int blinkLed = Config::Pins::BUILTIN_LED;
int ledState = true;

const int freq = 30;
const int cyclesBlink = 5;
const int sleeping = 5*60*1000;
double temperature;

void blink();

void setup()
{
    Serial.begin(115200);
    delay(5000);

    Serial.println();
    Serial.println("Initializing Dallas sensor...");
    temp.init();

    delay(1000);
    Serial.println("WiFi connecting...");
    wifi.connect();
    pinMode(blinkLed, OUTPUT);    
}

void loop() {
    temperature = temp.read();
        
    TemperaturePayload payload{
        temperature,
        Config::Device::DEVICE_NAME
    };
    
    if (!wifi.isConnected()) {
        wifi.connect();
    }
    
    ApiResponse response = client.sendTemperature(payload);

    Serial.printf("Temperaure: %.2f °C on device %s\n", temperature, Config::Device::DEVICE_NAME);
  
    blink();
    
    digitalWrite(blinkLed, LOW);

    delay(800);

    digitalWrite(blinkLed, HIGH);

    delay(sleeping);
}

// === Functions ===

void blink() {
    for (int i = 0; i < cyclesBlink; i++) {
        digitalWrite(blinkLed, LOW);
        delay(freq);
        digitalWrite(blinkLed, HIGH);
        delay(freq * 3);
    } 
}

