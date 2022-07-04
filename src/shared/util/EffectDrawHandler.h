#pragma once

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

public:
    CRGBA
    GetTextColor () const;

    CRGBA
    GetEffectColor () const;

    void UpdateTimers ();

    void CalculateDrawPosition ();
    void PrintEffectName ();
    void PrintSubtext ();
    void PrintEffectTimer ();

    void Draw (EffectInstance *instance, int idx, bool inset);

    static bool AreEffectsInset (int num);
    static void DrawAndXMore ();
    static void DrawRecentEffects (int num);
};
