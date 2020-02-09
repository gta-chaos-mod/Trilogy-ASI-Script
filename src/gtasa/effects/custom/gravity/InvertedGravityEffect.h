#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"

class InvertedGravityEffect : public EffectBase
{
public:
    InvertedGravityEffect ();

    void Disable () override;

    void HandleTick () override;
};
