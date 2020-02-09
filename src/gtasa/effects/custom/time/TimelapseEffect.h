#pragma once

#include "util/EffectBase.h"

#include "CClock.h"

class TimelapseEffect : public EffectBase
{
public:
    TimelapseEffect ();

    void Disable () override;

    void HandleTick () override;
};
