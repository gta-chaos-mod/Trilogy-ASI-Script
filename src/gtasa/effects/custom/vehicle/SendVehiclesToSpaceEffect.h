#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"
#include "util/RandomHelper.h"

class SendVehiclesToSpaceEffect : public EffectPlaceholder
{
public:
    SendVehiclesToSpaceEffect ();

    void Enable () override;
};
