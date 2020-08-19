#pragma once

#include "util/EffectBase.h"
#include "util/Teleportation.h"

#include "CCheat.h"

#include "CTaskSimpleCarSetPedOut.h"

class FreefallEffect : public EffectBase
{
public:
    FreefallEffect ();

    void HandleTick () override;
};
