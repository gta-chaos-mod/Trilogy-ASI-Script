#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "effects/EffectPlaceholder.h"

#include "util/GameUtil.h"

class OhHeyTanksEffect : public EffectPlaceholder
{
public:
	OhHeyTanksEffect();

	void Enable() override;

	bool CanActivate() override;

private:
	void SpawnTanks();

	float ToRadians(float angle);
};
