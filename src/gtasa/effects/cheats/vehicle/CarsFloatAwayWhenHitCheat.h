#pragma once

#include "util/EffectBase.h"

class CarsFloatAwayWhenHitCheat : public EffectBase
{
public:
	CarsFloatAwayWhenHitCheat();

	void Enable() override;
	void Disable() override;

	static void ApplyCollision(CVehicle* thisVehicle, CVehicle* a2, int a3, float* a4, int a5);
};
