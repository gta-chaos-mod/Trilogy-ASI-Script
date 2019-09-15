// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CBike.h"
#include "CBmx.h"
#include "CHeli.h"
#include "CModelInfo.h"
#include "CPlane.h"
#include "CShadows.h"
#include "CTrain.h"

class InvisibleVehicles : public TimedEffect
{
public:
	static bool onlyWheels;
	static bool isEnabled;

public:
	InvisibleVehicles(bool _onlyWheels, int duration, std::string description);

	void InitializeHooks() override;

	void Disable() override;

	void HandleTick() override;

	static void TryRenderAtomic(RwFrame* frameArray[], int size, int slot);

	static void __fastcall HookedRenderAutomobile(CAutomobile* thisAutomobile, void* edx);
	static void __fastcall HookedRenderHeli(CHeli* thisHeli, void* edx);
	static void __fastcall HookedRenderBike(CBike* thisBike, void* edx);
	static void __fastcall HookedRenderPlane(CPlane* thisPlane, void* edx);
	static void __fastcall HookedRenderEffects(CEntity* thisEntity, void* edx);
	static void HookedRenderShadows(CVehicle* thisVehicle, VEH_SHD_TYPE shadowType);

	static void __fastcall HookedCVehicleDoHeadLightBeam(CVehicle* thisVehicle, void* edx, int a2, CMatrix* matrix, char a4);
	static void __fastcall HookedCVehicleDoVehicleLights(CVehicle* thisVehicle, void* edx, int a2, CMatrix* matrix, int st);
};
