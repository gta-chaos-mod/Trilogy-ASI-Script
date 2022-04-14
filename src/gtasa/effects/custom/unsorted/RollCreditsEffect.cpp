#include <util/EffectBase.h>

#include "CCredits.h"

class RollCreditsEffect : public EffectBase
{
    int creditsStartTime = 0;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        if (!CCredits::bCreditsGoing)
        {
            CCredits::Start ();
            this->creditsStartTime = CCredits::CreditsStartTime;
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (CCredits::CreditsStartTime == this->creditsStartTime)
        {
            CCredits::Stop ();
        }
    }
};

DEFINE_EFFECT (RollCreditsEffect, "effect_roll_credits", 0);