#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

class NoVisibleWaterEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK (inst, Hooked_CGame_CanSeeWaterFromCurrArea, bool (), 0x6EB710);
    }

    static bool
    Hooked_CGame_CanSeeWaterFromCurrArea (auto &&cb)
    {
        return false;
    }
};

DEFINE_EFFECT (NoVisibleWaterEffect, "effect_no_visible_water", 0);