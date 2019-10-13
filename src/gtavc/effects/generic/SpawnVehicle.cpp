#include "SpawnVehicle.h"

SpawnVehicle::SpawnVehicle(int vehicleID)
	: EffectPlaceholder("spawn_vehicle")
{
	this->vehicleID = max(130, min(vehicleID, 236));
	if (this->vehicleID == 171 || this->vehicleID == 180 || this->vehicleID == 231) { // RC Bandit, Aeroplane, RC Goblin
		this->vehicleID = 153; // Mr. Whoopee
	}
}

void SpawnVehicle::Enable() {
	EffectBase::Enable();

	SpawnForPlayer();
}

void SpawnVehicle::SpawnForPlayer() {
	CPlayerPed* player = FindPlayerPed();
	if (player && !player->m_nInterior) {
		CVector position = player->TransformFromObjectSpace(CVector(0.0f, 5.0f, 1.0f));
		CVehicle* vehicle = CreateVehicle(position, player->m_fRotationCur);
	}
}

CVehicle* SpawnVehicle::CreateVehicle(CVector position, float orientation) {
	CVehicle* vehicle = nullptr;

	unsigned char oldFlags = CStreaming::ms_aInfoForModel[this->vehicleID].m_nFlags;
	CStreaming::RequestModel(this->vehicleID, 1);
	CStreaming::LoadAllRequestedModels(false);
	if (CStreaming::ms_aInfoForModel[this->vehicleID].m_nLoadState == LOADSTATE_LOADED) {
		if (!(oldFlags & 1)) {
			CStreaming::SetModelIsDeletable(this->vehicleID);
			CStreaming::SetModelTxdIsDeletable(this->vehicleID);
		}

		Command<eScriptCommands::COMMAND_CREATE_CAR>(this->vehicleID, position.x, position.y, position.z, &vehicle);

		if (vehicle) {
			CTheScripts::ClearSpaceForMissionEntity(position, vehicle);
		}
	}
	return vehicle;
}
