#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCarCtrl.h"

class BeybladeEffect : public EffectBase
{
public:
	BeybladeEffect();

	void Enable();

	void HandleTick();
};
