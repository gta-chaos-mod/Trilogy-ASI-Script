#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

class TurnVehiclesAroundEffect : public EffectPlaceholder
{
public:
	TurnVehiclesAroundEffect();

	void Enable() override;

private:
	void InvertVehicle(CMatrix matrix);
};
