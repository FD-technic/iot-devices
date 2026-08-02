#pragma once

#include "dto/Measurement.h"

class Sensor {
    public:
        virtual Measurement read() = 0;

        virtual ~Sensor() noexcept = default;
};
