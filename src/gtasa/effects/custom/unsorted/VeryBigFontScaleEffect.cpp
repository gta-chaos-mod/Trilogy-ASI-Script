#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class VeryBigFontScaleEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_ARGS (inst, Hooked_CFont_SetScale, void (float, float), 0x719380,
                   0x7193A0);
    }

    static void
    Hooked_CFont_SetScale (auto &&cb, float &width, float &height)
    {
        width *= 2.5f;
        height *= 2.5f;

        cb ();
    }
};

DEFINE_EFFECT (VeryBigFontScaleEffect, "effect_very_big_font_scale", 0);