#pragma once

#include "effects/EffectPlaceholder.h"

#include "CPlayerInfo.h"

class InstantlyHungryEffect : public EffectPlaceholder
{
public:
    InstantlyHungryEffect ();

    void Enable () override;
};
