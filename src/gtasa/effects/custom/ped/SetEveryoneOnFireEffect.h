#pragma once

#include "effects/EffectPlaceholder.h"

#include "CFireManager.h"

class SetEveryoneOnFireEffect : public EffectPlaceholder
{
public:
	SetEveryoneOnFireEffect();

	void Enable() override;
};
