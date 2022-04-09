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

    static std::string ToUpper (std::string string);

    static void ScaleWithRoot (RwMatrix *matrix, RwMatrix *root, RwV3d scale);

    static void RotateWithRoot (RwMatrix *matrix, RwMatrix *root, int axis,
                                float angle);
};
