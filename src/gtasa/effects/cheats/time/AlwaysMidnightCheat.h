#pragma once

#include "effects/TimedAddressEffect.h"

#include "CClock.h"

class AlwaysMidnightCheat : public TimedAddressEffect
{
public:
	AlwaysMidnightCheat();

	void HandleTick() override;
};
