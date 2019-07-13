#include "GhostRider.h"

GhostRider::GhostRider(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void GhostRider::Disable() {
	CVehicle* currentVehicle = FindPlayerVehicle(-1, false);
	if (currentVehicle) {
		currentVehicle->BlowUpCar(NULL, false);
	}
}

void GhostRider::HandleTick() {
	int step = (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);

	if (vehicleList.size() > 0) {
		auto it = vehicleList.begin();
		while (it != vehicleList.end()) {
			CVehicle* vehicle = it->first;

			if (vehicle) {
				vehicleList[vehicle] -= step;
				if (vehicleList[vehicle] < 0) {
					vehicleList.erase(it);
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
		if (vehicleList.contains(lastVehicle)) {
			auto it = vehicleList.find(lastVehicle);
			if (it != vehicleList.end()) {
				vehicleList.erase(it);
			}
		}

		currentVehicle->m_fHealth = 249.9f;
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
		case VEHICLE_BIKE: {
			*(float*)((char*)vehicle + 1980) = value;
		}
		case VEHICLE_AUTOMOBILE: {
			*(float*)((char*)vehicle + 2276) = value;
		}
	}
}