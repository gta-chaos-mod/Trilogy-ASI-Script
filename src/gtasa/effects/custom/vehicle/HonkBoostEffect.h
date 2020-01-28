#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"
#include "cHandlingDataMgr.h"

class HonkBoostEffect : public EffectBase
{
public:
	HonkBoostEffect();

	void HandleTick() override;
};
