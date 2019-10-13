#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"
#include "cHandlingDataMgr.h"

class LightspeedBrakingEffect : public EffectBase
{
private:
	tHandlingData origVehicleHandling[210] = {};

public:
	LightspeedBrakingEffect();

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
