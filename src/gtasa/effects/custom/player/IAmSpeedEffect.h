#pragma once

#include "util/EffectBase.h"

class IAmSpeedEffect : public EffectBase
{
public:
    IAmSpeedEffect ();

    void Enable () override;
    void Disable () override;
};
