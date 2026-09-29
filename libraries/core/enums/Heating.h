#pragma once

enum class HeatingMode {
    DAY,
    NIGHT,
    OFF,
    MANUAL
};

enum class ValveDirection {
    STOP,
    UP,
    DOWN
};

inline const char* heatingModeToString(HeatingMode heatingMode)
{
    switch (heatingMode)
    {
        case HeatingMode::DAY: return "DAY";
        case HeatingMode::NIGHT: return "NIGHT";
        case HeatingMode::OFF: return "OFF";
        case HeatingMode::MANUAL: return "MANUAL";
    }

    return "NIGHT";
};

inline const char* valveDirectionToString(ValveDirection direction)
{
    switch (direction)
    {
        case ValveDirection::STOP: return "STOP";
        case ValveDirection::UP:   return "UP";
        case ValveDirection::DOWN: return "DOWN";
    }

    return "STOP";
};