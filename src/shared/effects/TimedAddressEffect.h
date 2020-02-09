#pragma once

#include "util/EffectBase.h"

class TimedAddressEffect : public EffectBase
{
private:
    bool *address = nullptr;

public:
    TimedAddressEffect (std::string id, int address);

    void Disable () override;

    void HandleTick () override;
};
