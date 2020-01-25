#pragma once

#include <map>

#include "util/EffectBase.h"

#include "CAutomobile.h"
#include "CBike.h"
#include "CBoat.h"
#include "CModelInfo.h"

class GhostRiderEffect : public EffectBase
{
private:
	std::map<CVehicle*, int> vehicleList = {};
	CVehicle* lastVehicle = nullptr;

public:
	GhostRiderEffect();

	void Disable() override;

	void HandleTick() override;

private:
	void SetBurnTimer(CVehicle* vehicle, float value);
};
