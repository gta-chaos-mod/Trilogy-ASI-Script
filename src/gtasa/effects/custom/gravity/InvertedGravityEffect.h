#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"

class InvertedGravityEffect : public EffectBase
{
private:
	float gravity = -0.002f;

public:
	InvertedGravityEffect();

	void Disable() override;

	void HandleTick() override;
};
