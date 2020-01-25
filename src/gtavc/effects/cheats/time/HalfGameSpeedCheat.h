#pragma once

#include "util/EffectBase.h"

class HalfGameSpeedCheat : public EffectBase
{
public:
	HalfGameSpeedCheat();

	EffectBase* SetEffectDuration(int duration) override;

	void Disable() override;

	void HandleTick() override;
};
