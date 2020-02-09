#pragma once

#include "util/EffectBase.h"

class QuadrupleGameSpeedCheat : public EffectBase
{
public:
    QuadrupleGameSpeedCheat ();

    void Disable () override;

    void HandleTick () override;
};
