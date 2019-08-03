#pragma once

#include "TimedEffect.h"

#include "CAutomobile.h"
#include "CBike.h"
#include "CBoat.h"
#include "CModelInfo.h"

#include <map>

class GhostRider : public TimedEffect
{
private:
	std::map<CVehicle*, int> vehicleList;
	CVehicle* lastVehicle = nullptr;

public:
	GhostRider(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;

private:
	void SetBurnTimer(CVehicle* vehicle, float value);
};
