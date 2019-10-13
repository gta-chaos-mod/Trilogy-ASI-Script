#pragma once

#include "util/EffectBase.h"

class LockPlayerInsideVehicleEffect : public EffectBase
{
public:
	LockPlayerInsideVehicleEffect();

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
