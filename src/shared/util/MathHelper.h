#define _USE_MATH_DEFINES
#include <math.h>

class MathHelper
{
public:
    static float
    ToRadians (float degrees)
    {
        return (degrees * (float) M_PI) / 180.0f;
    }

    static float
    ToDegrees (float radians)
    {
        return (radians * 180.0f) / (float) M_PI;
    }
};