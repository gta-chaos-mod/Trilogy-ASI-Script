#include "FPS60Effect.h"

FPS60Effect::FPS60Effect () : EffectBase ("effect_fps_60")
{
    AddType ("framerate");
}

void
FPS60Effect::Enable ()
{
    EffectBase::Enable ();

    oldFrameTimeWait = injector::ReadMemory<byte> (0x53E94C, true);
    injector::WriteMemory<byte> (0x53E94C, 0, true);

    oldFramerate    = RsGlobal.frameLimit;
    oldFrameLimiter = FrontEndMenuManager.m_bFrameLimiterOn;
}

void
FPS60Effect::Disable ()
{
    injector::WriteMemory<byte> (0x53E94C, oldFrameTimeWait, true);
    RsGlobal.frameLimit                   = oldFramerate;
    FrontEndMenuManager.m_bFrameLimiterOn = oldFrameLimiter;

    EffectBase::Disable ();
}

void
FPS60Effect::HandleTick ()
{
    EffectBase::HandleTick ();

    RsGlobal.frameLimit                   = framerate;
    FrontEndMenuManager.m_bFrameLimiterOn = true;
}
