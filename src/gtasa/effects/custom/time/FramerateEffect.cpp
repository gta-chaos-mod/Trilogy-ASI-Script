#include "util/EffectBase.h"

#include <CMenuManager.h>

class FramerateEffect : public EffectBase
{
    int oldFramerate = 25;
    int framerate    = 25;

    bool oldFrameLimiter = false;

public:
    FramerateEffect (int framerate) : EffectBase ()
    {
        this->framerate = framerate;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->WriteMemory<byte> (0x53E94C, 0);

        this->oldFramerate    = RsGlobal.maxFPS;
        this->oldFrameLimiter = FrontEndMenuManager.m_bFrameLimiterOn;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        RsGlobal.maxFPS                       = this->oldFramerate;
        FrontEndMenuManager.m_bFrameLimiterOn = this->oldFrameLimiter;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        RsGlobal.maxFPS                       = this->framerate;
        FrontEndMenuManager.m_bFrameLimiterOn = true;
    }
};

DEFINE_EFFECT (FramerateEffect, "effect_fps_15", GROUP_FRAMERATE, 15);
DEFINE_EFFECT (FramerateEffect, "effect_fps_60", GROUP_FRAMERATE, 60);