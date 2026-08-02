#pragma once

#include <stdint.h>

enum class PeriodType : uint8_t
{
    DAY,
    WEEK,
    MONTH,
    QUARTER,
    HALF,
    YEAR,
    ALL
};

inline const char* toString(PeriodType type)
{
    switch (type)
    {
        case PeriodType::DAY:
            return "DAY";

        case PeriodType::WEEK:
            return "WEEK";

        case PeriodType::MONTH:
            return "MONTH";

            case PeriodType::QUARTER:
            return "QUARTER";

        case PeriodType::HALF:
            return "HALF";

        case PeriodType::YEAR:
            return "YEAR";
        
        case PeriodType::ALL:
            return "ALL";

        default:
            return "UNKNOWN";
    }
}