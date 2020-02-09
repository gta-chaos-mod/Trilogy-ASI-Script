#pragma once

#include "effects/EffectPlaceholder.h"

#include "util/GameUtil.h"

class RemoveAllWeaponsEffect : public EffectPlaceholder
{
public:
    RemoveAllWeaponsEffect ();

    void Enable () override;
};
