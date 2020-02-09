#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"

class QuarterGravityEffect : public EffectBase
{
private:
    float gravity = 0.002f;

public:
    QuarterGravityEffect ();

    void Disable () override;

    void HandleTick () override;
};
