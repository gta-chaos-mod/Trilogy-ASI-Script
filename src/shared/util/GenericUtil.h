#pragma once

#include "util/MathHelper.h"

#include <CMenuManager.h>
#include <CTimer.h>

// Adapted from CLEO
// Returns a hex version number in the following format:
// 0x0v0v0v
// 0x0v0v0v
#define MOD_VERSION_MAJOR 3
#define MOD_VERSION_MINOR 3
#define MOD_VERSION_PATCH 0

#define MOD_VERSION                                                            \
    ((MOD_VERSION_MAJOR << 16) | (MOD_VERSION_MINOR << 8) | MOD_VERSION_PATCH)

class GenericUtil
{
public:
    static std::string GetModVersion ();

    static float CalculateTick (float multiplier = 1.0);

    static std::string FormatTime (int duration, bool onlySeconds = false);

    static bool IsMenuActive ();

    static float EaseOutBack (float t);

    /* Ease Out Back transition with a specific range */
    static float
    EaseOutBack (float t, float min, float max)
    {
        return EaseOutBack (t) * (max - min) + min;
    }

    static float EaseInOutQubic (float t);

    static float
    EaseInOutQubic (float t, float min, float max)
    {
        return EaseInOutQubic (t) * (max - min) + min;
    }

    static std::string ToUpper (std::string string);
};
