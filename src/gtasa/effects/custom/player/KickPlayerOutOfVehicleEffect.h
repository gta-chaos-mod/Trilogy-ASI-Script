#pragma once

#include "effects/EffectPlaceholder.h"

#include "CTaskSimpleCarSetPedOut.h"

class KickPlayerOutOfVehicleEffect : public EffectPlaceholder
{
public:
	KickPlayerOutOfVehicleEffect();

	void Enable() override;
};
