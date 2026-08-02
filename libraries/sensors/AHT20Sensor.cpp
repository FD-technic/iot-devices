#include "AHT20Sensor.h"

AHT20Sensor::AHT20Sensor(const String& sensorName)
    : sensorName(sensorName)
{
}

bool AHT20Sensor::init()
{
    available = aht.begin();
    return available;
}

Measurement AHT20Sensor::read() {
    
    Serial.print("Is Available: ");
    Serial.println(available);
    if (!available) {
        return Measurement(
            sensorName,
            MeasurementType::HUMIDITY,
            NAN
        );
    }
    sensors_event_t humidity;
    sensors_event_t temperature;

    aht.getEvent(&humidity, &temperature);

    return Measurement(
        sensorName,
        MeasurementType::HUMIDITY,
        humidity.relative_humidity
    );
}