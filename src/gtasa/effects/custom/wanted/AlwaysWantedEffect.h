#pragma once

#include "util/EffectBase.h"

class AlwaysWantedEffect : public EffectBase
{
public:
    AlwaysWantedEffect ();

    void HandleTick () override;
};
