#pragma once

#include "util/EffectBase.h"

#include "CGame.h"
#include "CPopulation.h"
#include "CStreaming.h"
#include "CTimeCycle.h"
#include "CWorld.h"

class Teleport : public EffectBase
{
private:
	CVector destination;

public:
	Teleport(CVector destination);

	void Enable() override;
};
