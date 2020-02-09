#include "QuarterGameSpeedCheat.h"

QuarterGameSpeedCheat::QuarterGameSpeedCheat ()
    : EffectBase ("cheat_quarter_game_speed")
{
    AddType ("game_speed");
}

EffectBase *
QuarterGameSpeedCheat::SetEffectDuration (int duration)
{
    EffectBase::SetEffectDuration (duration / 3);
    return this;
}

void
QuarterGameSpeedCheat::Disable ()
{
    CTimer::ms_fTimeScale = 1.0f;

    EffectBase::Disable ();
}

void
QuarterGameSpeedCheat::HandleTick ()
{
    EffectBase::HandleTick ();

    CTimer::ms_fTimeScale = 0.25f;
}
