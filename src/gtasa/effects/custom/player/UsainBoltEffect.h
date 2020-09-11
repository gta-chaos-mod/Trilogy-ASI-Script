#pragma once

#include "util/EffectBase.h"

class UsainBoltEffect : public EffectBase
{
public:
    UsainBoltEffect ();

    void Enable () override;
    void Disable () override;
};
