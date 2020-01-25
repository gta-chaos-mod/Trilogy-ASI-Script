#pragma once

#include "effects/EffectPlaceholder.h"

class SetCurrentVehicleOnFireEffect : public EffectPlaceholder
{
public:
	SetCurrentVehicleOnFireEffect();

	void Enable() override;
};
