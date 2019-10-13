#include "SendVehiclesToSpaceEffect.h"

SendVehiclesToSpaceEffect::SendVehiclesToSpaceEffect()
	: EffectPlaceholder("cheat_send_vehicles_to_space") {}

void SendVehiclesToSpaceEffect::Enable() {
	EffectPlaceholder::Enable();

	GameUtil::SetVehiclesToRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_vecMoveSpeed.z = 10.0f;
	}
}
