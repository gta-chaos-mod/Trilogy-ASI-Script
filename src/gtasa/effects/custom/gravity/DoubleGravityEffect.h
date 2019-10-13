#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"

class DoubleGravityEffect : public EffectBase
{
private:
	float gravity = 0.016f;

public:
	DoubleGravityEffect();

	void Disable() override;

	void HandleTick() override;
};
