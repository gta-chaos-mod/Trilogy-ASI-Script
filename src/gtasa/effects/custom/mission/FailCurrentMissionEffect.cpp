#include "FailCurrentMissionEffect.h"

FailCurrentMissionEffect::FailCurrentMissionEffect()
	: EffectPlaceholder("effect_fail_current_mission") {}

void FailCurrentMissionEffect::Enable() {
	EffectPlaceholder::Enable();

	if (CTheScripts::IsPlayerOnAMission()) {
		Command<Commands::CLEAR_SMALL_PRINTS>();
		Command<Commands::PRINT_BIG_Q>("M_FAIL", 5000, 1);

		for (auto i = CTheScripts::pActiveScripts; i; i = i->m_pNext) {
			if (i->m_bIsMission && i->m_bIsActive && !i->m_bIsExternal) {
				Teleportation::TeleportOutOfMission(GenericUtil::ToUpper(std::string(i->m_szName)));
				break;
			}
		}
	}
	Command<Commands::FAIL_CURRENT_MISSION>();
	CGangWars::EndGangWar(false);

	GameUtil::RemovePlayerBalaclava();
}
