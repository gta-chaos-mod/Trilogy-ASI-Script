#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"
#include "cHandlingDataMgr.h"

class ZeroSuspensionDampingEffect : public EffectBase
{
private:
	tHandlingData origVehicleHandling[106] = {};
	float suspension = -1.0f;

public:
	ZeroSuspensionDampingEffect();

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
