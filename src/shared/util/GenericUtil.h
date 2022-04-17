#pragma once

#include <util/MathHelper.h>

#include "CMenuManager.h"
#include "CTimer.h"

class GenericUtil
{
public:
    static std::string GetModVersion ();

    static float CalculateTick (float multiplier = 1.0f);

    static std::string FormatTime (int duration, bool onlySeconds = false);

    static bool IsMenuActive ();

    static float EaseOutBack (float t);

    /* Ease Out Back transition with a specific range */
    static float
    EaseOutBack (float t, float min, float max)
    {
        return EaseOutBack (t) * (max - min) + min;
    }

    static std::string ToUpper (std::string string);
};
