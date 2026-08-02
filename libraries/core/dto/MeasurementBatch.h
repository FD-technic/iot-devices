#pragma once

#include <vector>
#include "dto/Measurement.h"

struct MeasurementBatch
{
    String deviceName;
    std::vector<Measurement> measurements;
    
    MeasurementBatch() = default;

    explicit MeasurementBatch(const String& deviceName)
        : deviceName(deviceName)
    {
        
    }

    void add(const Measurement& measurement)
    {
        measurements.push_back(measurement);
    }

    void clear()
    {
        measurements.clear();
    }
};