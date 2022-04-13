#pragma once

class EffectInstance;

class EffectDrawHandler
{
    /* Draw context variables */
    inline static EffectInstance* effect;
    
    inline static int  idx;
    inline static bool isInset;

    inline static float x = 0;
    inline static float y = 0;

    /* Effect specific variables */
    float transitionTimer = 0;
    int   textFlashTimer  = 2400;
    bool  textFlashingThisFrame = true;

    CRGBA textColor     = CRGBA (255, 255, 255, 255);
    CRGBA flashColor    = CRGBA (255, 255, 0, 255);
    CRGBA disabledColor = CRGBA (175, 175, 175, 255);

public:
    CRGBA
    GetTextColor () const;

    CRGBA
    GetEffectColor () const;

    void UpdateTimers ();
    
    void CalculateDrawPosition ();
    void PrintEffectName ();
    void PrintEffectVoter ();
    void PrintEffectTimer ();

    void Draw (EffectInstance *instance, int idx, bool inset);

    static bool AreEffectsInset (int num);
    static void DrawRecentEffects (int num);
};
