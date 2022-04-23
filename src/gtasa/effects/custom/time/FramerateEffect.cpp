#include <util/EffectBase.h>

#include <CMenuManager.h>

class FramerateEffect : public EffectBase
{
    int oldFramerate = 25;
    int framerate    = 25;

    byte oldFrameTimeWait = 14;
    bool oldFrameLimiter  = false;

public:
    FramerateEffect (int framerate) : EffectBase ()
    {
        this->framerate = framerate;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        this->oldFrameTimeWait = injector::ReadMemory<byte> (0x53E94C, true);
        injector::WriteMemory<byte> (0x53E94C, 0, true);

        this->oldFramerate    = RsGlobal.frameLimit;
        this->oldFrameLimiter = FrontEndMenuManager.m_bFrameLimiterOn;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        injector::WriteMemory<byte> (0x53E94C, this->oldFrameTimeWait, true);
        RsGlobal.frameLimit                   = this->oldFramerate;
        FrontEndMenuManager.m_bFrameLimiterOn = this->oldFrameLimiter;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        RsGlobal.frameLimit                   = this->framerate;
        FrontEndMenuManager.m_bFrameLimiterOn = true;
    }
};

DEFINE_EFFECT (FramerateEffect, "effect_fps_15", GROUP_FRAMERATE, 15);
DEFINE_EFFECT (FramerateEffect, "effect_fps_60", GROUP_FRAMERATE, 60);