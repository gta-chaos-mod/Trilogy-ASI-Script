#pragma once

#include "util/EffectBase.h"
#include "util/RandomHelper.h"

class EverybodyBleedNowEffect : public EffectBase
{
private:
    int   wait             = 0;
    bool *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    EverybodyBleedNowEffect ();

    void Disable () override;

    void HandleTick () override;
};
