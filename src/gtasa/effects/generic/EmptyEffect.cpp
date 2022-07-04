#pragma once

#include "effects/OneTimeEffect.h"

class EmptyEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        inst->OverrideName (
            inst->GetCustomData ().value ("name", "Empty Effect"));
    }
};

DEFINE_EFFECT (EmptyEffect, "effect__generic_empty", 0);