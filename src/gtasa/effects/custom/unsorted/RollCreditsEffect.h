#pragma once

#include "util/EffectBase.h"

#include "CCredits.h"

class RollCreditsEffect : public EffectBase
{
private:
    int CreditsStartTime = 0;

public:
    RollCreditsEffect ();

    void Enable () override;
    void Disable () override;
};
