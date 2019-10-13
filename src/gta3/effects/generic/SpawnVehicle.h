#pragma once

#include "effects/EffectPlaceholder.h"

#include "CCarCtrl.h"
#include "CStreaming.h"
#include "CModelInfo.h"
#include "CVehicleModelInfo.h"
#include "CWorld.h"

#include "CAutomobile.h"
#include "CBoat.h"
#include "CHeli.h"
#include "CPlane.h"

#include "extensions/ScriptCommands.h"

class SpawnVehicle : public EffectPlaceholder
{
private:
	int vehicleID = 0;

public:
	SpawnVehicle(int vehicleID);

	void Enable() override;

private:
	void SpawnForPlayer();
	CVehicle* CreateVehicle(CVector position, float orientation);
};
