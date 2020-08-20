#include "RollCreditsEffect.h"
#include "Events.h"
#include "CPed.h"
#include "common.h"
#include "ePedBones.h"
#include <CCredits.h>

RollCreditsEffect::RollCreditsEffect () : EffectBase ("roll_credits_effect") {}

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
        CCredits::Stop ();

    EffectBase::Disable ();
}
