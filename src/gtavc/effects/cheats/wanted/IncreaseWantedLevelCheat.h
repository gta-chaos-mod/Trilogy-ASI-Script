#pragma once

#include "effects/EffectPlaceholder.h"

class IncreaseWantedLevelCheat : public EffectPlaceholder
{
public:
	IncreaseWantedLevelCheat();

	void Enable() override;
};
