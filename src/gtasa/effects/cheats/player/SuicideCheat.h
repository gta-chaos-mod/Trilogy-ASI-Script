#pragma once

#include "effects/EffectPlaceholder.h"

#include "CCheat.h"

class SuicideCheat : public EffectPlaceholder
{
public:
    SuicideCheat ();

    void Enable () override;
};
