#include "util/EffectBase.h"
#include "util/Globals.h"

class HideChaosUIEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Globals::isHideChaosUIEffectEnabled = true;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Globals::isHideChaosUIEffectEnabled = false;
    }
};

DEFINE_EFFECT (HideChaosUIEffect, "effect_hide_chaos_ui", 0);
