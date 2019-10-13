#pragma once

#include "effects/EffectPlaceholder.h"

class GetBustedEffect : public EffectPlaceholder
{
public:
	GetBustedEffect();

	void Enable() override;
};
