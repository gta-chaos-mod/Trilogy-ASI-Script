#include "ExperienceTheLagEffect.h"

ExperienceTheLagEffect::ExperienceTheLagEffect ()
    : EffectBase ("effect_experience_the_lag")
{
    AddType ("game_speed");
}

void
ExperienceTheLagEffect::Disable ()
{
    CTimer::ms_fTimeScale = 1.0f;

    EffectBase::Disable ();
}

void
ExperienceTheLagEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    if (wait > 0)
    {
        wait -= CalculateTick ();
        return;
    }

    CTimer::ms_fTimeScale = RandomHelper::Random (0.1f, 2.0f);

    GameUtil::SetVehiclesToRealPhysics ();

    wait = RandomHelper::Random (50, 200);
}
