#include "FakePassCurrentMissionEffect.h"

FakePassCurrentMissionEffect::FakePassCurrentMissionEffect()
	: EffectPlaceholder("effect_fake_pass_current_mission")
{
	SetCanTickWhenDisabled();
}

void FakePassCurrentMissionEffect::HandleTick() {
	EffectBase::HandleTick();

	if (handledEverything) {
		return;
	}

	if (!handledMission) {
		bool wasOnMission = CTheScripts::IsPlayerOnAMission();
		if (wasOnMission) {
			Command<Commands::CLEAR_SMALL_PRINTS>();
			Command<Commands::PRINT_BIG_Q>("M_PASSD", 5000, 1);
			Command<Commands::PLAY_MISSION_PASSED_TUNE>(1);

			CPlayerPed* player = FindPlayerPed();
			if (player) {
				player->SetWantedLevel(0);
			}

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

		handledMission = true;

		if (wasOnMission) {
			EffectDatabase::QueueEffect(new AutosaveEffect(GameUtil::GetRealMissionsPassed()), true);
		}
	}
	else {
		if (wait > 0) {
			wait -= CalculateTick();
			return;
		}

		bool isOnMission = CTheScripts::IsPlayerOnAMission();

		if (isOnMission && !lastIsOnMission && handledMission) {
			SetDescription(GetDescription().append("?"));
			handledMission = false;
			handledEverything = true;

			Disable();
		}

		lastIsOnMission = isOnMission;
	}
}
