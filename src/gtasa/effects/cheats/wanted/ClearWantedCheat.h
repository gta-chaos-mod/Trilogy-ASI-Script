#pragma once

#include "effects/EffectPlaceholder.h"

class ClearWantedCheat : public EffectPlaceholder
{
public:
    ClearWantedCheat ();

    void Enable () override;
};
