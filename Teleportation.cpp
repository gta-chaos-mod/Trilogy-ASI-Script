#include "Teleportation.h"

void Teleportation::Teleport(CVector destination) {
	CEntity* entity = FindPlayerEntity(-1);
	if (entity) {
		entity->Teleport(destination, false);

		CGame::currArea = 0;
		entity->m_nAreaCode = 0;

		CPed* player = FindPlayerPed();
		if (player) {
			player->m_nAreaCode = 0;
			player->m_pEnex = 0;
		}

		CTimeCycle::StopExtraColour(false);
	}
}
