#include "SpawnVehicleEffect.h"

SpawnVehicleEffect::SpawnVehicleEffect(int vehicleID)
	: EffectPlaceholder("effect_spawn_vehicle")
{
	this->vehicleID = max(400, min(vehicleID, 611));
	if (this->vehicleID == 569) {
		this->vehicleID = 537; // 569 crashes the game when spawned in apparently
	}
}

void SpawnVehicleEffect::Enable() {
	EffectPlaceholder::Enable();

	SpawnForPlayer();
}

void SpawnVehicleEffect::SpawnForPlayer() {
	CPlayerPed* player = FindPlayerPed();
	if (player && !player->m_nAreaCode) {
		CVector position = player->TransformFromObjectSpace(CVector(0.0f, 5.0f, 0.0f));
		CVehicle* vehicle = CreateVehicle(position, player->m_fCurrentRotation + 1.5707964f);
	}
}

CVehicle* SpawnVehicleEffect::CreateVehicle(CVector position, float orientation) {
	unsigned char oldFlags = CStreaming::ms_aInfoForModel[this->vehicleID].m_nFlags;
	CStreaming::RequestModel(this->vehicleID, GAME_REQUIRED);
	CStreaming::LoadAllRequestedModels(false);
	if (CStreaming::ms_aInfoForModel[this->vehicleID].m_nLoadState == LOADSTATE_LOADED) {
		if (!(oldFlags & GAME_REQUIRED)) {
			CStreaming::SetModelIsDeletable(this->vehicleID);
			CStreaming::SetModelTxdIsDeletable(this->vehicleID);
		}
		CVehicle* vehicle = nullptr;
		switch (reinterpret_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[this->vehicleID])->m_nVehicleType) {
			case VEHICLE_MTRUCK:
				vehicle = new CMonsterTruck(this->vehicleID, 1);
				break;
			case VEHICLE_QUAD:
				vehicle = new CQuadBike(this->vehicleID, 1);
				break;
			case VEHICLE_HELI:
				vehicle = new CHeli(this->vehicleID, 1);
				break;
			case VEHICLE_PLANE:
				vehicle = new CPlane(this->vehicleID, 1);
				break;
			case VEHICLE_BIKE:
				vehicle = new CBike(this->vehicleID, 1);
				reinterpret_cast<CBike*>(vehicle)->m_nDamageFlags |= 0x10;
				break;
			case VEHICLE_BMX:
				vehicle = new CBmx(this->vehicleID, 1);
				reinterpret_cast<CBmx*>(vehicle)->m_nDamageFlags |= 0x10;
				break;
			case VEHICLE_TRAILER:
				vehicle = new CTrailer(this->vehicleID, 1);
				break;
			case VEHICLE_BOAT:
			case VEHICLE_TRAIN: // Thank you Rockstar, very cool
				vehicle = new CBoat(this->vehicleID, 1);
				break;
			default:
				vehicle = new CAutomobile(this->vehicleID, 1, true);
				break;
		}
		if (vehicle) {
			vehicle->SetPosn(position);
			vehicle->SetOrientation(0.0f, 0.0f, orientation);
			vehicle->m_nStatus = eEntityStatus::STATUS_ABANDONED;
			vehicle->m_nDoorLock = CARLOCK_UNLOCKED;
			CTheScripts::ClearSpaceForMissionEntity(position, vehicle);
			CWorld::Add(vehicle);
			if (vehicle->m_nVehicleClass == VEHICLE_BIKE)
				reinterpret_cast<CBike*>(vehicle)->PlaceOnRoadProperly();
			else if (vehicle->m_nVehicleClass != VEHICLE_BOAT)
				reinterpret_cast<CAutomobile*>(vehicle)->PlaceOnRoadProperly();

			return vehicle;
		}
	}
	return nullptr;
}
