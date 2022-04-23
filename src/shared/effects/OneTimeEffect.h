#pragma once

#include "util/EffectBase.h"

class OneTimeEffect : public EffectBase
{
public:
    virtual void
    OnTick (EffectInstance *instance) final
    {
        instance->Disable ();
    }
};
