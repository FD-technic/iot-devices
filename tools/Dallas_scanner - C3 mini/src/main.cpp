#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 10   // Změň podle svého GPIO

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (deviceAddress[i] < 16)
            Serial.print("0");

        Serial.print(deviceAddress[i], HEX);

        if (i < 7)
            Serial.print(":");
    }
    Serial.println();
}

void setup()
{
    Serial.begin(115200);

    sensors.begin();

    Serial.println("Dallas Scanner");
    Serial.println("----------------");

    uint8_t count = sensors.getDeviceCount();

    Serial.print("Devices found: ");
    Serial.println(count);

    DeviceAddress address;

    for (uint8_t i = 0; i < count; i++)
    {
        if (sensors.getAddress(address, i))
        {
            Serial.print("Sensor ");
            Serial.print(i);
            Serial.print(": ");

            printAddress(address);
        }
        else
        {
            Serial.print("Cannot read address of sensor ");
            Serial.println(i);
        }
    }
}

void loop()
{
}