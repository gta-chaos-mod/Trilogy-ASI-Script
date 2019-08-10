#include "HookHandler.h"

bool HookHandler::canLoadSave = true;

void HookHandler::Initialize() {
	// True Pacifist + Long Live The Rich + Infinite Health
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

	// Inverted Controls / Lets Take A Break / Disable One Movement Key
	int processMenuOptions[] = {
		0x0576AE9,
		0x0577244,
		0x0577266,
		0x05772C2,
		0x05772E5,
		0x057730F,
		0x0578E26,
		0x0578EA1,
		0x057B73A,
		0x057C4AB,
		0x057C4B3,
		0x057C4BB,
		0x057C4C3,
		0x057D2D9,
		0x057D306,
		0x057D315,
		0x057D335,
		0x057D379,
		0x057D38A,
		0x057D6AB,
		0x057D6BA
	};
	for (int address : processMenuOptions) {
		patch::RedirectCall(address, HookedProcessMenuOptions);
	}
}

void __fastcall HookHandler::HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo) {
	if (TruePacifist::isEnabled) {
		return;
	}

	if (LongLiveTheRich::isEnabled && LongLiveTheRich::HandleArmour(thisCalc, ped, cDamageResponseInfo)) {
		return;
	}

	thisCalc->AccountForPedArmour(ped, cDamageResponseInfo);
}

void __fastcall HookHandler::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4) {
	if (InfiniteHealth::isEnabled) {
		return;
	}
	
	if (TruePacifist::isEnabled) {
		if (thisCalc->m_pDamager->m_nType == eEntityType::ENTITY_TYPE_PED) {
			return;
		}
	}

	if (LongLiveTheRich::isEnabled && LongLiveTheRich::HandleHealth(thisCalc, ped, a3, a4)) {
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

void __fastcall HookHandler::HookedProcessMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_LOAD_GAME) { // NO LOADING :AngryBongo:
		if (!canLoadSave) {
			return;
		}
		canLoadSave = false;
	}

	if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS) {
		if (InvertedControls::isEnabled || LetsTakeABreak::isEnabled || DisableOneMovementKey::isEnabled) {
			return;
		}
	}

	thisManager->SwitchToNewScreen(page);
}
