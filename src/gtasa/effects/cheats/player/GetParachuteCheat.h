#pragma once

#include "effects/EffectPlaceholder.h"

#include "CCheat.h"

class GetParachuteCheat : public EffectPlaceholder
{
public:
	GetParachuteCheat();

	void Enable() override;
};
