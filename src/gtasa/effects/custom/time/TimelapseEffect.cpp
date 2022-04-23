#include "util/EffectBase.h"

#include <CClock.h>

class TimelapseEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        CClock::ms_nMillisecondsPerGameMinute = 1000;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CClock::ms_nMillisecondsPerGameMinute = 10;
    }
};

DEFINE_EFFECT (TimelapseEffect, "effect_timelapse", GROUP_TIME);