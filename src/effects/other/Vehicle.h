// Copyright (c) 2019 Lordmau5
#pragma once

#include "plugin.h"
#include "common.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <random>

#include "cHandlingDataMgr.h"
#include "CBoat.h"
#include "CBmx.h"
#include "CCarCtrl.h"
#include "CHeli.h"
#include "CModelInfo.h"
#include "CMonsterTruck.h"
#include "CPlane.h"
#include "CQuadBike.h"
#include "CStreaming.h"
#include "CTimer.h"
#include "CTheScripts.h"
#include "CTrailer.h"
#include "CTrain.h"
#include "CWorld.h"

class Vehicle
{
public:
	static void SpawnVehicle(int modelID, CVector position, float orientation);
	static void SpawnForPlayer(int modelID);
	static void BlowUpAllCars();

	static void FixPlayerVehicle();
	static void SetPlayerVehicleOnFire();
	static void PopAllVehicleTires();
	static void SendVehiclesToSpace();
	static void TurnVehiclesAround();

private:
	static void InvertVehicle(CMatrix* matrix);
};
