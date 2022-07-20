#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

class MathHelper
{
public:
    static double
    ToRadians (double degrees)
    {
        return (degrees * M_PI) / 180.0;
    }

    static double
    ToDegrees (double radians)
    {
        return (radians * 180.0) / M_PI;
    }
};