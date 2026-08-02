#pragma once

#include <stdint.h>

enum class MeasurementType : uint8_t
{
    TEMPERATURE,
    HUMIDITY,
    PRESSURE,

    RSSI,
    UPTIME,

    BATTERY,
    VOLTAGE,

    DIGITAL_INPUT,
    DIGITAL_OUTPUT,

    UNKNOWN
};

constexpr const char* toString(MeasurementType type)
{
    switch (type)
    {
        case MeasurementType::TEMPERATURE:
            return "TEMPERATURE";

        case MeasurementType::HUMIDITY:
            return "HUMIDITY";

        case MeasurementType::PRESSURE:
            return "PRESSURE";

        case MeasurementType::RSSI:
            return "RSSI";

        case MeasurementType::UPTIME:
            return "UPTIME";

        case MeasurementType::BATTERY:
            return "BATTERY";

        case MeasurementType::VOLTAGE:
            return "VOLTAGE";

        case MeasurementType::DIGITAL_INPUT:
            return "DIGITAL_INPUT";

        case MeasurementType::DIGITAL_OUTPUT:
            return "DIGITAL_OUTPUT";

        case MeasurementType::UNKNOWN:
        default:
            return "UNKNOWN";
    }
}