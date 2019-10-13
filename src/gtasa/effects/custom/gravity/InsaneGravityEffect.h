#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"

class InsaneGravityEffect : public EffectBase
{
private:
	float gravity = 0.64f;

public:
	InsaneGravityEffect();

	void Disable() override;

	void HandleTick() override;
};
