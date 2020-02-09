#include "QuadrupleGameSpeedCheat.h"

QuadrupleGameSpeedCheat::QuadrupleGameSpeedCheat ()
    : EffectBase ("cheat_quadruple_game_speed")
{
    AddType ("game_speed");
}

void
QuadrupleGameSpeedCheat::Disable ()
{
    CTimer::ms_fTimeScale = 1.0f;

    EffectBase::Disable ();
}

void
QuadrupleGameSpeedCheat::HandleTick ()
{
    EffectBase::HandleTick ();

    CTimer::ms_fTimeScale = 4.0f;
}
