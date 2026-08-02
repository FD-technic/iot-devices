#include "Bmp280Sensor.h"

Bmp280Sensor::Bmp280Sensor(const String& sensorName)
    : sensorName(sensorName)
{
}

bool Bmp280Sensor::init()
{
    return bmp.begin(0x77);
}

Measurement Bmp280Sensor::read()
{
    double pressure = bmp.readPressure() / 100.0;

    if ( std::isnan(pressure)) {
        pressure = 111.11;
    }

    return Measurement(
        sensorName,
        MeasurementType::PRESSURE,
        pressure
    );
}