#pragma once

#include "effects/EffectPlaceholder.h"

#include "CGame.h"
#include "CPopulation.h"
#include "CStreaming.h"
#include "CTimeCycle.h"
#include "CWorld.h"

class Teleport : public EffectPlaceholder
{
private:
	CVector destination;

public:
	Teleport(CVector destination);

	void Enable() override;
};
