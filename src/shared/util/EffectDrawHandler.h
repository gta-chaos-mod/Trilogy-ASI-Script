#pragma once

#include "util/Config.h"

#define DRAW_LEFT Config::GetOrDefault ("Drawing.DrawOnLeftSide", true)
#define RECENT_EFFECTS                                                         \
    std::max (3,                                                               \
              std::min (8,                                                     \
                        Config::GetOrDefault ("Drawing.NumRecentEffects", 6)))

class EffectInstance;

class EffectDrawHandler
{
    /* Draw context variables */
    static inline EffectInstance *effect;

    static inline int  idx;
    static inline bool isInset;

    static inline float x = 0;
    static inline float y = 0;

    /* Effect specific variables */
    float transitionTimer       = 0;
    int   textFlashTimer        = 2400;
    bool  textFlashingThisFrame = true;

    CRGBA textColor     = plugin::color::White;
    CRGBA flashColor    = plugin::color::Yellow;
    CRGBA disabledColor = plugin::color::DarkGray;

    struct ScreensaverHUDElement
    {
        CVector2D pos;
        float     speedModifier = 1.0f;
        bool      goingRight    = false;
        bool      goingDown     = false;
    };

    static inline std::map<std::string, ScreensaverHUDElement> positions = {};

public:
    CRGBA
    GetTextColor () const;

    CRGBA
    GetEffectColor () const;

    static CRGBA GetDropShadowColor ();

    void UpdateTimers ();

    void CalculateDrawPosition ();
    void PrintEffectName ();
    void PrintSubtext ();
    void PrintEffectTimer ();

    void Draw (EffectInstance *instance, int idx, bool inset);

    static bool AreEffectsInset ();
    static void DrawAndXMore ();
    static void DrawRecentEffects ();

    static ScreensaverHUDElement CreateHUDElement (EffectInstance *effect);
    static void                  Tick ();

    static void ClearScreensaverHUDMap ();
};
