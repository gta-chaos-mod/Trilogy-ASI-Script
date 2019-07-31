#include "Vehicle.h"

static bool didCopyHandling;
static tHandlingData origVehicleHandling[210];

void Vehicle::SpawnVehicle(int modelID, CVector position, float orientation) {
	if (modelID == 569) {
		modelID = 537; // 569 Crashes when being placed as a boat, so replace with 537
	}

	unsigned char oldFlags = CStreaming::ms_aInfoForModel[modelID].m_nFlags;
	CStreaming::RequestModel(modelID, GAME_REQUIRED);
	CStreaming::LoadAllRequestedModels(false);
	if (CStreaming::ms_aInfoForModel[modelID].m_nLoadState == LOADSTATE_LOADED) {
		if (!(oldFlags & GAME_REQUIRED)) {
			CStreaming::SetModelIsDeletable(modelID);
			CStreaming::SetModelTxdIsDeletable(modelID);
		}
		CVehicle* vehicle = nullptr;
		switch (reinterpret_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[modelID])->m_nVehicleType) {
		case VEHICLE_MTRUCK:
			vehicle = new CMonsterTruck(modelID, 1);
			break;
		case VEHICLE_QUAD:
			vehicle = new CQuadBike(modelID, 1);
			break;
		case VEHICLE_HELI:
			vehicle = new CHeli(modelID, 1);
			break;
		case VEHICLE_PLANE:
			vehicle = new CPlane(modelID, 1);
			break;
		case VEHICLE_BIKE:
			vehicle = new CBike(modelID, 1);
			reinterpret_cast<CBike*>(vehicle)->m_nDamageFlags |= 0x10;
			break;
		case VEHICLE_BMX:
			vehicle = new CBmx(modelID, 1);
			reinterpret_cast<CBmx*>(vehicle)->m_nDamageFlags |= 0x10;
			break;
		case VEHICLE_TRAILER:
			vehicle = new CTrailer(modelID, 1);
			break;
		case VEHICLE_BOAT:
			vehicle = new CBoat(modelID, 1);
			break;
		case VEHICLE_TRAIN:
			vehicle = new CBoat(modelID, 1); // Thank you Rockstar, very cool
			break;
		default:
			vehicle = new CAutomobile(modelID, 1, true);
			break;
		}
		if (vehicle) {
			vehicle->SetPosn(position);
			vehicle->SetOrientation(0.0f, 0.0f, orientation);
			vehicle->m_nStatus = eEntityStatus::STATUS_ABANDONED;
			vehicle->m_nDoorLock = CARLOCK_UNLOCKED;
			CWorld::Add(vehicle);
			CTheScripts::ClearSpaceForMissionEntity(position, vehicle);
			if (vehicle->m_nVehicleClass == VEHICLE_BIKE)
				reinterpret_cast<CBike*>(vehicle)->PlaceOnRoadProperly();
			else if (vehicle->m_nVehicleClass != VEHICLE_BOAT)
				reinterpret_cast<CAutomobile*>(vehicle)->PlaceOnRoadProperly();
		}
	}
}

void Vehicle::SpawnForPlayer(int modelID) {
	CPlayerPed* player = FindPlayerPed();
	if (player && !player->m_nAreaCode) {
		CVector position = player->TransformFromObjectSpace(CVector(0.0f, 5.0f, 0.0f));
		Vehicle::SpawnVehicle(modelID, position, player->m_fCurrentRotation + 1.5707964f);
	}
}

void Vehicle::BlowUpAllCars() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bExplosionProof = false;
		vehicle->BlowUpCar(NULL, false);
	}
}

void Vehicle::SetPlayerVehicleOnFire() {
	CVehicle* playerVehicle = FindPlayerVehicle(-1, false);
	if (playerVehicle) {
		playerVehicle->m_fHealth = 249.9f;
	}
}

void Vehicle::PopAllVehicleTires() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bBulletProof = false;

		vehicle->BurstTyre(eWheels::WHEEL_FRONT_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_RIGHT, true);
	}
}

void Vehicle::StairwayToHeaven() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}

		vehicle->m_vecMoveSpeed.z = 10.0f;
	}
}

void Vehicle::TurnVehiclesAround() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}

		CMatrixLink* matrix = vehicle->GetMatrix();
		InvertVehicle(matrix);

		vehicle->m_vecMoveSpeed.x = -vehicle->m_vecMoveSpeed.x;
		vehicle->m_vecMoveSpeed.y = -vehicle->m_vecMoveSpeed.y;
		vehicle->m_vecMoveSpeed.z = -vehicle->m_vecMoveSpeed.z;
	}
}

void Vehicle::SetSuspension(float suspension) {
	if (!didCopyHandling) {
		for (int i = 0; i < 210; i++) {
			origVehicleHandling[i] = gHandlingDataMgr.m_aVehicleHandling[i];
		}

		didCopyHandling = true;
	}

	for (int i = 0; i < 210; i++) {
		gHandlingDataMgr.m_aVehicleHandling[i].m_fSuspensionDampingLevel = suspension;
	}
}

void Vehicle::ResetSuspension() {
	for (int i = 0; i < 210; i++) {
		gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
	}
}

void Vehicle::InvertVehicle(CMatrix* matrix) {
	matrix->right.x = -matrix->right.x;
	matrix->right.y = -matrix->right.y;
	matrix->right.z = -matrix->right.z;

	matrix->up.x = -matrix->up.x;
	matrix->up.y = -matrix->up.y;
	matrix->up.z = -matrix->up.z;
}