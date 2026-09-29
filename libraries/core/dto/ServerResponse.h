#ifndef SERVER_RESPONSE_H
#define SERVER_RESPONSE_H

#include "enums/Heating.h"

struct RemoteTemperatures {
    float outdoor = 15.0;
    float indoor = 21.0;
};

struct TargetTemperatures {
    float room = 21.0;
    float waterHeater = 60.0;
    float heatingHysteresis = 5;
    float waterHeatingHysteresis = 3;
};

struct ManualControl {
    bool waterHeaterPump = false;
    bool heatingPump = false;
    ValveDirection valveDirection = ValveDirection::STOP;
};

struct ServerResponse {
    RemoteTemperatures remote;
    TargetTemperatures target;
    HeatingMode heatingMode = HeatingMode::DAY;
    ManualControl manual;
};

#endif