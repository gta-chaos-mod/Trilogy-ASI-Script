#pragma once

#include "util/EffectBase.h"

class DoubleGameSpeedCheat : public EffectBase
{
public:
    DoubleGameSpeedCheat ();

    void Disable () override;

    void HandleTick () override;
};
