#pragma once

#include "util/EffectBase.h"

class RollCreditsEffect : public EffectBase
{
    int CreditsStartTime;

public:
    RollCreditsEffect ();

    void Enable () override;
    void Disable () override;
};
