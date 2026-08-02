#pragma once

#include <stdint.h>

enum class DeviceType : uint8_t
{
    WEATHER,
    THERMOMETER,
    IRRIGATION,
    CONTROLLER
};

inline const char* toString(DeviceType type)
{
    switch (type)
    {
        case DeviceType::WEATHER:
            return "WEATHER";

        case DeviceType::THERMOMETER:
            return "THERMOMETER";

        case DeviceType::IRRIGATION:
            return "IRRIGATION";

        case DeviceType::CONTROLLER:
            return "CONTROLLER";

        default:
            return "UNKNOWN";
    }
}