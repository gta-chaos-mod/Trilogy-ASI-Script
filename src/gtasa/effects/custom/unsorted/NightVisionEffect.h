#pragma once

#include "util/EffectBase.h"

#include "extensions/ScriptCommands.h"

class NightVisionEffect : public EffectBase
{
public:
    NightVisionEffect ();

    void Disable () override;

    void HandleTick () override;
};
