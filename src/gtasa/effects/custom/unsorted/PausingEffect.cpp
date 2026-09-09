#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CMenuManager.h>

class PausingEffect : public EffectBase
{
    int wait = 1000 * 10;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        FrontEndMenuManager.m_bStartUpFrontEndRequested = true;

        wait = inst->Random (1000 * 10, 1000 * 30);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        FrontEndMenuManager.m_bStartUpFrontEndRequested = true;

        wait = inst->Random (1000 * 10, 1000 * 30);
    }
};

DEFINE_EFFECT (PausingEffect, "effect_pausing", 0);