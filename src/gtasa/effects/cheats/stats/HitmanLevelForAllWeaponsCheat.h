#pragma once

#include "effects/EffectPlaceholder.h"

#include "CStats.h"

class HitmanLevelForAllWeaponsCheat : public EffectPlaceholder
{
public:
	HitmanLevelForAllWeaponsCheat();

	void Enable() override;
};
