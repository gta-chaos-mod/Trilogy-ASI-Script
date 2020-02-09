#pragma once

#include "effects/EffectPlaceholder.h"

#include "CFireManager.h"

class SetAllPedsOnFireEffect : public EffectPlaceholder
{
public:
    SetAllPedsOnFireEffect ();

    void Enable () override;
};
