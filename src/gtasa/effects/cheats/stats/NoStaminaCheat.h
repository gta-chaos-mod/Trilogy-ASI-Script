#pragma once

#include "effects/EffectPlaceholder.h"

#include "CStats.h"

class NoStaminaCheat : public EffectPlaceholder
{
public:
	NoStaminaCheat();

	void Enable() override;
};
