#pragma once

#include "effects/EffectPlaceholder.h"

class RemoveAllWeaponsEffect : public EffectPlaceholder
{
public:
	RemoveAllWeaponsEffect();

	void Enable() override;
};
