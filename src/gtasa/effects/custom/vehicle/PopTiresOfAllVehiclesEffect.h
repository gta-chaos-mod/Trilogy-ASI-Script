#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

class PopTiresOfAllVehiclesEffect : public EffectBase
{
public:
	PopTiresOfAllVehiclesEffect();

	void HandleTick() override;
};
