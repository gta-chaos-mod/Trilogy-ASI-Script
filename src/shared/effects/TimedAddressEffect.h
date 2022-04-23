#pragma once

#include <util/EffectBase.h>

class TimedAddressEffect : public EffectBase
{
    bool *address;

public:
    TimedAddressEffect (int address)
    {
        this->address = reinterpret_cast<bool *> (address);
    }

    void
    OnEnd (EffectInstance *instance) override
    {
        if (address) *address = false;
    }

    void
    OnTick (EffectInstance *instance) override
    {
        if (address) *address = true;
    }
};
