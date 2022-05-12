#include "util/EffectBase.h"

#include <CClock.h>

using namespace plugin;

class TimelapseEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD (inst, Hooked_CSimpleVariablesSaveStructure_Construct,
                     int (void *), 0x5D14AE);
    }

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

    static int
    Hooked_CSimpleVariablesSaveStructure_Construct (auto &&cb)
    {
        CClock::ms_nMillisecondsPerGameMinute = 1000;

        int result = cb ();

        CClock::ms_nMillisecondsPerGameMinute = 10;

        return result;
    }
};

DEFINE_EFFECT (TimelapseEffect, "effect_timelapse", GROUP_TIME);