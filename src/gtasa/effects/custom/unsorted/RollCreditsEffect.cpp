#include "util/EffectBase.h"

#include <CCredits.h>
#include <CTimer.h>

class RollCreditsEffect : public EffectBase
{
    int creditsStartTime = 0;

public:
    void
    OnEnd (EffectInstance *inst) override
    {
        if (CCredits::CreditsStartTime == this->creditsStartTime)
        {
            CCredits::Stop ();
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CCredits::bCreditsGoing)
        {
            CCredits::Start ();
            this->creditsStartTime = CCredits::CreditsStartTime;
        }
    }
};

DEFINE_EFFECT (RollCreditsEffect, "effect_roll_credits", 0);