#pragma once

#include "util/EffectBase.h"

class YourCarFloatsAwayWhenHitEffect : public EffectBase
{
private:
	static bool collisionHappened;

public:
	YourCarFloatsAwayWhenHitEffect();

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static void ApplyCollision(CVehicle* thisVehicle, CVehicle* a2, int a3, float* a4, int a5);
};
