#include "RollCreditsEffect.h"

RollCreditsEffect::RollCreditsEffect () : EffectBase ("effect_roll_credits") {}

void
RollCreditsEffect::Enable ()
{
    EffectBase::Enable ();

    if (!CCredits::bCreditsGoing)
    {
        CCredits::Start ();
        CreditsStartTime = CCredits::CreditsStartTime;
    }
}

void
RollCreditsEffect::Disable ()
{
    if (CCredits::CreditsStartTime == CreditsStartTime)
    {
        CCredits::Stop ();
    }

    EffectBase::Disable ();
}