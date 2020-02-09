#pragma once

#include "effects/EffectPlaceholder.h"

class SuicideCheat : public EffectPlaceholder
{
public:
    SuicideCheat ();

    void Enable () override;
};
