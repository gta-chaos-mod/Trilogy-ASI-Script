#include "GhostRider.h"

GhostRider::GhostRider(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void GhostRider::Disable() {
	CVehicle* currentVehicle = FindPlayerVehicle(-1, false);
	if (currentVehicle) {
		currentVehicle->m_nPhysicalFlags.bExplosionProof = false;
		currentVehicle->BlowUpCar(NULL, false);
	}
}

void GhostRider::HandleTick() {
	int step = CalculateTick();

	if (vehicleList.size() > 0) {
		auto it = vehicleList.begin();
		while (it != vehicleList.end()) {
			CVehicle* vehicle = it->first;

			if (vehicle) {
				vehicleList[vehicle] -= step;
				if (vehicleList[vehicle] < 0) {
					vehicleList.erase(it);
					vehicle->m_nPhysicalFlags.bExplosionProof = false;
					vehicle->BlowUpCar(NULL, false);
				}
			} 
			else {
				vehicleList.erase(it);
			}

			it++;
		}
	}

	CVehicle* currentVehicle = FindPlayerVehicle(-1, false);

	if (currentVehicle) {
		if (vehicleList.contains(currentVehicle)) {
			auto it = vehicleList.find(currentVehicle);
			if (it != vehicleList.end()) {
				vehicleList.erase(it);
			}
		}

		SetBurnTimer(currentVehicle, 0.0f);
	}
	else if (!currentVehicle && lastVehicle && !vehicleList.contains(lastVehicle))
	{
		vehicleList[lastVehicle] = 5000;
		lastVehicle->m_fHealth = 1000.0f;
	}

	lastVehicle = currentVehicle;
}

void GhostRider::SetBurnTimer(CVehicle* vehicle, float value) {
	switch (reinterpret_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[vehicle->m_nModelIndex])->m_nVehicleType) {
		case VEHICLE_BIKE:
		case VEHICLE_BMX: {
			CBike* bike = (CBike*)vehicle;
			bike->m_fHealth = 249.0f;
			//bike->field_7BC = (int)value; // This should also be a float, until then we use the float pointer
			*(float*)((char*)vehicle + 1980) = value;
		}
		case VEHICLE_AUTOMOBILE:
		case VEHICLE_MTRUCK:
		case VEHICLE_QUAD:
		case VEHICLE_TRAILER: {
			CAutomobile* automobile = (CAutomobile*)vehicle;
			automobile->m_fHealth = 249.0f;
			//automobile->m_dwBurnTimer = (int)value; // This should be a float, until then we use the float pointer
			*(float*)((char*)vehicle + 2276) = value;
		}
		case VEHICLE_BOAT: {
			CBoat* boat = (CBoat*)vehicle;
			boat->m_fHealth = 249.0f;
			boat->m_fBurningTimer = value;
		}
	}
}