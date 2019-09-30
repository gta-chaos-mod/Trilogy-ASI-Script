// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CBike.h"
#include "CBmx.h"
#include "CBoat.h"
#include "CHeli.h"
#include "CModelInfo.h"
#include "CPlane.h"
#include "CShadows.h"
#include "CTrain.h"

class InvisibleVehicles : public TimedEffect
{
public:
	static bool onlyWheels;

	bool oldForceVehicleLightsOff = false;

public:
	InvisibleVehicles(bool _onlyWheels, int duration, const std::string& description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static void TryRenderAtomic(RwFrame* frameArray[], int size, int slot);

	static void __fastcall HookedRenderAutomobile(CAutomobile* thisAutomobile);
	static void __fastcall HookedRenderHeli(CHeli* thisHeli);
	static void __fastcall HookedRenderBike(CBike* thisBike);
	static void __fastcall HookedRenderPlane(CPlane* thisPlane);
	static void __fastcall HookedRenderTrain(CTrain* thisTrain);
	static void __fastcall HookedRenderBoat(CBoat* thisBoat);
	static uint8_t* HookedRwIm3DTransform(uint8_t* pVerts, signed int numVerts, RwMatrix* ltm, unsigned int flags);
	static void __fastcall HookedRenderEffects(CEntity* thisEntity);
	static void HookedRenderShadows(CVehicle* thisVehicle, VEH_SHD_TYPE shadowType);

	static void __fastcall HookedCVehicleDoHeadLightBeam(CVehicle* thisVehicle, void* edx, int a2, CMatrix* matrix, char a4);
	static void __fastcall HookedCVehicleAddExhaustParticles(CVehicle* thisVehicle);
	static void __fastcall HookedCVehicleAddWaterSplashParticles(CVehicle* thisVehicle);
	static void __fastcall HookedCVehicleAddSingleWheelParticles(CVehicle* thisVehicle, void* edx, int wheelState, int a3,
		float a4, float a5, CColPoint* a6, RwV3d* from, int a8, signed int a9, int _surfaceType, int _bloodState, char a12);
	static void __fastcall HookedCVehicleAddDamagedVehicleParticles(CVehicle* thisVehicle);
};
