#include "ExplodeAllVehiclesCheat.h"

ExplodeAllVehiclesCheat::ExplodeAllVehiclesCheat()
	: EffectPlaceholder("cheat_explode_all_vehicles") {}

void ExplodeAllVehiclesCheat::Enable() {
	EffectPlaceholder::Enable();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle) {
			vehicle->BlowUpCar(nullptr);
		}
	}
}
