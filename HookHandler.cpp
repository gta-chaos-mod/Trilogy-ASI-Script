#include "HookHandler.h"

void HookHandler::Initialize() {
	// TruePacifist + MoneyIsHealthy
	patch::RedirectCall(0x4B5B19, HookedAccountForPedArmour);
	patch::RedirectCall(0x4B5B27, HookedComputeWillKillPed);

	// Invisible Vehicles
	patch::RedirectCall(0x6C4523, InvisibleVehicles::HookedRenderHeli); // Heli
	patch::RedirectCall(0x6BDE5E, InvisibleVehicles::HookedRenderBike); // Bike + Bmx
	patch::RedirectJump(0x6CAB80, InvisibleVehicles::HookedRenderPlane); // Plane

	patch::RedirectCall(0x5343B2, InvisibleVehicles::HookedRenderEffects);

	patch::RedirectCall(0x6ABCF5, InvisibleVehicles::HookedRenderShadows); // Car Shadows
	patch::RedirectCall(0x6C0B21, InvisibleVehicles::HookedRenderShadows); // BMX Shadows
	patch::RedirectCall(0x6C58A0, InvisibleVehicles::HookedRenderShadows); // Heli Shadows
	patch::RedirectCall(0x6BD667, InvisibleVehicles::HookedRenderShadows); // Bike Shadows
	patch::RedirectCall(0x6CA73A, InvisibleVehicles::HookedRenderShadows); // Plane Shadows

	// Rainbow Cars
	Events::vehicleRenderEvent += RenderVehicleEvent;

	// Disable HUD
	patch::RedirectCall(0x53E4FF, HookedHUDDraw);

	// Disable Radar Blips
	patch::RedirectJump(0x58AA2D, HookedBlipsDraw);
	patch::RedirectCall(0x575B44, HookedBlipsDraw);
}

void __fastcall HookHandler::HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo) {
	if (TruePacifist::isEnabled) {
		return;
	}

	if (LongLiveTheRich::isEnabled) {
		LongLiveTheRich::HandleArmour(thisCalc, ped, cDamageResponseInfo);
		return;
	}

	thisCalc->AccountForPedArmour(ped, cDamageResponseInfo);
}

void __fastcall HookHandler::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4) {
	if (TruePacifist::isEnabled) {
		return;
	}

	if (LongLiveTheRich::isEnabled) {
		LongLiveTheRich::HandleHealth(thisCalc, ped, a3, a4);
		return;
	}

	thisCalc->ComputeWillKillPed(ped, a3, a4);
}

void HookHandler::RenderVehicleEvent(CVehicle* vehicle) {
	if (RainbowCars::isEnabled) {
		RainbowCars::ModifyCarPaint(vehicle);
	}
}

void HookHandler::HookedHUDDraw() {
	if (DisableHUD::isEnabled) {
		CRadar::Draw3dMarkers();
	}
	else {
		CHud::Draw();
	}
}

void HookHandler::HookedBlipsDraw() {
	if (!DisableHUD::isEnabled && !DisableRadarBlips::isEnabled) {
		CRadar::DrawBlips();
	}
}