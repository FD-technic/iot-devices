#pragma once

#include <Arduino.h>
#include "../enums/DeviceType.h"

struct Device
{
    String name;
    String description;
    String firmware;
    DeviceType type;
};