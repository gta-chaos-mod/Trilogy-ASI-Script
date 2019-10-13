#pragma once

#include "effects/EffectPlaceholder.h"

#include "CStreaming.h"
#include "CModelInfo.h"
#include "CVehicleModelInfo.h"
#include "CWorld.h"

#include "CAutomobile.h"
#include "CBike.h"
#include "CBmx.h"
#include "CBoat.h"
#include "CHeli.h"
#include "CMonsterTruck.h"
#include "CPlane.h"
#include "CQuadBike.h"
#include "CTrailer.h"

class SpawnVehicleEffect : public EffectPlaceholder
{
private:
	int vehicleID = 0;

public:
	SpawnVehicleEffect(int vehicleID);

	void Enable() override;

private:
	void SpawnForPlayer();
	CVehicle* CreateVehicle(CVector position, float orientation);
};
