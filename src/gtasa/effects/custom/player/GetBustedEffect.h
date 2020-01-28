#pragma once

#include "util/EffectBase.h"

#include "CCutsceneMgr.h"

class GetBustedEffect : public EffectBase
{
public:
	GetBustedEffect();

	void HandleTick() override;
};
