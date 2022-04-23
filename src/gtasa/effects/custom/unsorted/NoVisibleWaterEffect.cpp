#include "util/EffectBase.h"

using namespace plugin;

class NoVisibleWaterEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x6EB710, Hooked_CGame_CanSeeWaterFromCurrArea);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // Revert
        injector::MakeCALL (0x6EB710,
                            0x53C4B0); // CGame::CanSeeWaterFromCurrArea
    }

    static bool
    Hooked_CGame_CanSeeWaterFromCurrArea ()
    {
        return false;
    }
};

DEFINE_EFFECT (NoVisibleWaterEffect, "effect_no_visible_water", 0);