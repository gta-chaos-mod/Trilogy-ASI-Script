#pragma once

#include "effects/TimedAddressEffect.h"

class SmashNBoomCheat : public TimedAddressEffect
{
public:
	SmashNBoomCheat();

	void HandleTick() override;
};
