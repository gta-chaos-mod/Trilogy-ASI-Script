#pragma once

#include "effects/EffectPlaceholder.h"

#include "CWorld.h"

class FullArmorCheat : public EffectPlaceholder
{
public:
    FullArmorCheat ();

    void Enable () override;
};
