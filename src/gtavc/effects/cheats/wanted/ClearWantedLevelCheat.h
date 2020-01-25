#pragma once

#include "effects/EffectPlaceholder.h"

class ClearWantedLevelCheat : public EffectPlaceholder
{
public:
	ClearWantedLevelCheat();

	void Enable() override;
};
