#pragma once

#include <stdint.h>

enum class DeviceType : uint8_t
{
    THERMOMETER,
    IRRIGATION,
    RELAY
};

inline const char* toString(DeviceType type)
{
    switch (type)
    {
        case DeviceType::THERMOMETER:
            return "THERMOMETER";

        case DeviceType::IRRIGATION:
            return "IRRIGATION";

        case DeviceType::RELAY:
            return "RELAY";

        default:
            return "UNKNOWN";
    }
}