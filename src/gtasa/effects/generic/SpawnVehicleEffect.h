#pragma once

#include "effects/EffectPlaceholder.h"

#include "util/GameUtil.h"

#include "extensions/ScriptCommands.h"

class SpawnVehicleEffect : public EffectPlaceholder
{
private:
	int vehicleID = 0;
	bool setPlayerAsDriver = false;

public:
	SpawnVehicleEffect(int vehicleID);
	SpawnVehicleEffect(int vehicleID, bool setPlayerAsDriver);

	void Enable() override;

	bool CanActivate() override;

private:
	void SpawnForPlayer();
};
