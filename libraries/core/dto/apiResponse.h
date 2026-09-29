#pragma once

#include "dto/ServerResponse.h"
struct ApiResponse
{
    int httpCode;
    bool ledEnabled;

    ServerResponse data;
};

struct PeripheralStatus
{
    String deviceName;
    HeatingMode heatingMode;
    ValveDirection valveDirection;
    bool heatingPump; 
    bool waterHeaterPump; 
};
