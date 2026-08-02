#include <Arduino.h>
#include "enums/MeasurementType.h"

#pragma once

struct Measurement
{
    String sensorName;
    MeasurementType type;
    double value;

    Measurement(
        const String& sensorName,
        MeasurementType type,
        double value)
        : sensorName(sensorName),
          type(type),
          value(value)
    {
    }
};