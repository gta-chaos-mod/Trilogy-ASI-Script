#pragma once

using namespace plugin;

class DrawHelper
{
    static inline int         remaining = 0;
    static inline int         cooldown  = 0;
    static inline std::string mode      = "";

    static std::string GetCooldownString ();
    static float       CalculateBarWidth ();

public:
    static void UpdateCooldown (int _remaining, int _cooldown,
                                std::string _mode);

    static void Tick ();

    static void Draw ();

    static void DrawEffects ();
    static void DrawVersion ();
    static void DrawTopBar ();
    static void DrawRecentEffects ();

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
