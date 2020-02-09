#pragma once

#include "plugin.h"

#define _USE_MATH_DEFINES

#include <math.h>

#define deg2rad(angleDegrees) ((angleDegrees) *M_PI / 180.0)

#include "Config.h"
#include "DrawVoting.h"
#include "EffectBase.h"
#include "EffectDatabase.h"
#include "GenericUtil.h"

#include "CFont.h"
#include "CTimer.h"
#include "extensions/FontPrint.h"

using namespace plugin;

class DrawHelper
{
private:
    static int         remaining;
    static int         cooldown;
    static std::string mode;

    static std::string GetCooldownString ();
    static float       CalculateBarWidth ();

public:
    static void UpdateCooldown (int _remaining, int _cooldown,
                                std::string _mode);

    static void Draw ();

    static void DrawVersion ();
    static void DrawTopBar ();
    static void DrawRecentEffects ();

public:
    static void DrawCircle (CVector2D position, float radius, float angle,
                            CRGBA color);
    static void AppendPie (RwIm2DVertex *vertices, int numCount, float radius,
                           CVector2D center, float pie, CRGBA color,
                           float baseRotation);
    static void Transform (RwIm2DVertex *vertices, int numCount,
                           CVector2D transformation);
    static void Append (RwIm2DVertex *vertices, int index, CVector2D coord,
                        CRGBA color, RwReal u = 0, RwReal v = 0);
    static void Rotate (RwIm2DVertex *vertices, int numCount, CVector2D origin,
                        float angle);
};
