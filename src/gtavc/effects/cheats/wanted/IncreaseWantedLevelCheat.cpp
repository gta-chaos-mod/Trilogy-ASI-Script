#include "IncreaseWantedLevelCheat.h"

IncreaseWantedLevelCheat::IncreaseWantedLevelCheat()
	: EffectPlaceholder("cheat_increase_wanted_level") {}

void IncreaseWantedLevelCheat::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player && player->m_pWanted) {
		int level = min(player->GetWantedLevel() + 2, 6);
		player->m_pWanted->CheatWantedLevel(level);
	}
}
