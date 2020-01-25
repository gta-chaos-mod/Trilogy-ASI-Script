#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"
#include "cHandlingDataMgr.h"

class LittleSuspensionDampingEffect : public EffectBase
{
private:
	tHandlingData origVehicleHandling[106] = {};
	float suspension = 0.001f;

public:
	LittleSuspensionDampingEffect();

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
