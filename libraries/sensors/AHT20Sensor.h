#pragma once

#include <Adafruit_AHTX0.h>

#include "Sensor.h"

class AHT20Sensor : public Sensor {
    public:
        AHT20Sensor(const String& sensorName);

        bool init();
        Measurement read() override;

    private:
        String sensorName;
        Adafruit_AHTX0 aht;
        bool available = false;
};