#include "SpawnVehicle.h"

SpawnVehicle::SpawnVehicle(int vehicleID)
	: EffectPlaceholder("spawn_vehicle")
{
	this->vehicleID = max(90, min(vehicleID, 150));
	if (this->vehicleID == 131 || this->vehicleID == 140) { // RC Bandit, Aeroplane
		this->vehicleID = 113; // Mr. Whoopee
	}
}

void SpawnVehicle::Enable() {
	EffectBase::Enable();

	SpawnForPlayer();
}

void SpawnVehicle::SpawnForPlayer() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		CVector position = player->TransformFromObjectSpace(CVector(0.0f, 5.0f, 0.0f));
		CVehicle* vehicle = CreateVehicle(position, player->m_fRotationCur + 1.5707964f);
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
