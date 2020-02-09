#pragma once

#include "util/EffectBase.h"

class QuarterGameSpeedCheat : public EffectBase
{
public:
    QuarterGameSpeedCheat ();

    EffectBase *SetEffectDuration (int duration) override;

    void Disable () override;

    void HandleTick () override;
};
