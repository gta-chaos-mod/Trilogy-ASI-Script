#include "util/EffectBase.h"

#include <CClock.h>

using namespace plugin;

class TimelapseEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x5D14AE,
                            Hooked_CSimpleVariablesSaveStructure_Construct);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CClock::ms_nMillisecondsPerGameMinute = 1000;

        injector::MakeCALL (0x5D14AE, 0x5D1B80);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CClock::ms_nMillisecondsPerGameMinute = 10;
    }

    static int __fastcall Hooked_CSimpleVariablesSaveStructure_Construct (
        void *thisStructure)
    {
        CClock::ms_nMillisecondsPerGameMinute = 1000;
        int result = CallMethodAndReturn<int, 0x5D1B80, void *> (thisStructure);
        CClock::ms_nMillisecondsPerGameMinute = 10;

        return result;
    }
};

DEFINE_EFFECT (TimelapseEffect, "effect_timelapse", GROUP_TIME);