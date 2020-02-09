#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"
#include "cHandlingDataMgr.h"

class HighSuspensionDampingEffect : public EffectBase
{
private:
    tHandlingData origVehicleHandling[210] = {};
    float         suspension               = 10.0f;

public:
    HighSuspensionDampingEffect ();

    void Enable () override;
    void Disable () override;

    void HandleTick () override;
};
