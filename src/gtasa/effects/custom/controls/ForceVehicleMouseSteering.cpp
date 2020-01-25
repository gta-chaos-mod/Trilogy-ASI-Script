#include "ForceVehicleMouseSteering.h"

ForceVehicleMouseSteering::ForceVehicleMouseSteering()
	: EffectBase("effect_force_vehicle_mouse_steering")
{
	AddType("controls");
}

void ForceVehicleMouseSteering::Enable() {
	EffectBase::Enable();

	for (int i = 0; i < 59; i++) {
		origActions[i] = ControlsManager.m_actions[i];
	}

	oldMouseSteering = CVehicle::m_bEnableMouseSteering;
}

void ForceVehicleMouseSteering::Disable() {
	CVehicle::m_bEnableMouseSteering = oldMouseSteering;

	for (int i = 0; i < 59; i++) {
		ControlsManager.m_actions[i] = origActions[i];
	}

	EffectBase::Disable();
}

void ForceVehicleMouseSteering::HandleTick() {
	EffectBase::HandleTick();

	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	ControlsManager.m_actions[CA_VEHICLE_STEERLEFT] = CControllerAction();
	ControlsManager.m_actions[CA_VEHICLE_STEERRIGHT] = CControllerAction();

	CVehicle::m_bEnableMouseSteering = true;

	wait = 100;
}

FILESTREAM ForceVehicleMouseSteering::HookedOpenFile(const char* file, const char* mode) {
	return 0;
}

void __fastcall ForceVehicleMouseSteering::HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS) {
		return;
	}

	GameFixes::HookedProcessMenuOptions(thisManager, edx, page);
}
