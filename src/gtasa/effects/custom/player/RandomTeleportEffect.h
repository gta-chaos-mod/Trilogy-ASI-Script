#pragma once

#include "util/EffectBase.h"
#include "util/Teleportation.h"
#include "util/RandomHelper.h"

#include "CWorld.h"

class RandomTeleportEffect : public EffectBase
{
public:
    RandomTeleportEffect ();

    void HandleTick () override;
};
