#pragma once

#include <Adafruit_BMP280.h>

#include "Sensor.h"

class Bmp280Sensor : public Sensor {
    public:
        Bmp280Sensor(const String& sensorName);

        bool init();
        Measurement read() override;

    private:
        String sensorName;
        Adafruit_BMP280 bmp;
};