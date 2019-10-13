#pragma once

#include "effects/EffectPlaceholder.h"

#include "CPlayerInfo.h"

class HealthArmorMoneyCheat : public EffectPlaceholder
{
public:
	HealthArmorMoneyCheat();

	void Enable() override;
};
