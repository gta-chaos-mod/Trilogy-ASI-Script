#include "SetCurrentVehicleOnFireEffect.h"

SetCurrentVehicleOnFireEffect::SetCurrentVehicleOnFireEffect()
	: EffectPlaceholder("cheat_set_current_vehicle_on_fire") {}

void SetCurrentVehicleOnFireEffect::Enable() {
	EffectPlaceholder::Enable();

	CVehicle* playerVehicle = FindPlayerVehicle(-1, false);
	if (playerVehicle) {
		playerVehicle->m_nPhysicalFlags.bFireProof = false;
		playerVehicle->m_fHealth = 249.9f;
	}
}
