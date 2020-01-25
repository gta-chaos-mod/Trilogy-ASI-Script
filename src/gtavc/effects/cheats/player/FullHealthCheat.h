#pragma once

#include "effects/EffectPlaceholder.h"

class FullHealthCheat : public EffectPlaceholder
{
public:
	FullHealthCheat();

	void Enable() override;
};
