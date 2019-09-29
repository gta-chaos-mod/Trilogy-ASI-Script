// Copyright (c) 2019 Lordmau5
#include "Teleportation.h"

void Teleportation::Teleport(CVector destination, bool toOverworld) {
	CEntity* entity = FindPlayerEntity(-1);
	if (entity) {
		entity->Teleport(destination, false);

		if (toOverworld) {
			CGame::currArea = 0;
			entity->m_nAreaCode = 0;

			CEntryExitManager::ms_entryExitStackPosn = 0;
			CPopulation::bInPoliceStation = false;
			CStreaming::RemoveBuildingsNotInArea(0);

			CWorld::Remove(entity);
			CWorld::Add(entity);

			CPed* player = FindPlayerPed();
			if (player) {
				player->m_nAreaCode = 0;
				player->m_pEnex = 0;

				CWorld::Remove(player);
				CWorld::Add(player);
			}

			plugin::Call<0x40A560>(); // CStreaming::StreamZoneModels
			CTimeCycle::StopExtraColour(false);
		}
	}
}
