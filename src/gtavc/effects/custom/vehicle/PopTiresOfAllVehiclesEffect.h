#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

class PopTiresOfAllVehiclesEffect : public EffectPlaceholder
{
public:
	PopTiresOfAllVehiclesEffect();

	void Enable() override;
};
