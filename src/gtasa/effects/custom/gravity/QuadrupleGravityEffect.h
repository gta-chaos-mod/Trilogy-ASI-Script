#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"

class QuadrupleGravityEffect : public EffectBase
{
private:
	float gravity = 0.032f;

public:
	QuadrupleGravityEffect();

	void Disable() override;

	void HandleTick() override;
};
