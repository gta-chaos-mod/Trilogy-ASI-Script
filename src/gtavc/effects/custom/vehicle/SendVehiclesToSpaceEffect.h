#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

class SendVehiclesToSpaceEffect : public EffectPlaceholder
{
public:
    SendVehiclesToSpaceEffect ();

    void Enable () override;
};
