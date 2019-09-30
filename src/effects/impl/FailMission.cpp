// Copyright (c) 2019 Lordmau5
#include "FailMission.h"

FailMission::FailMission(bool _fakePass, int _duration, const std::string& _description)
	: EffectPlaceholder(_duration, _description) {
	fakePass = _fakePass;
}

void FailMission::HandleTick() {
	if (handledEverything) {
		return;
	}

	if (!handledMission) {
		if (CTheScripts::IsPlayerOnAMission()) {
			if (fakePass) {
				Command<Commands::CLEAR_SMALL_PRINTS>();
				Command<Commands::PRINT_BIG_Q>("M_PASSD", 5000, 1);
				Command<Commands::PLAY_MISSION_PASSED_TUNE>(1);

				CPlayerPed* player = FindPlayerPed();
				if (player) {
					player->SetWantedLevel(0);
				}
			}
			else {
				Command<Commands::CLEAR_SMALL_PRINTS>();
				Command<Commands::PRINT_BIG_Q>("M_FAIL", 5000, 1);
			}
		}
		Command<Commands::FAIL_CURRENT_MISSION>();
		CGangWars::EndGangWar(false);

		Player::RemoveBalaclava();

		handledMission = true;
		SetTextColor(false);

		// TODO: Add "Autosave" message for it as well
	}
	else {
		if (wait > 0) {
			wait -= CalculateTick();
			return;
		}

		bool isOnMission = CTheScripts::IsPlayerOnAMission();

		if (isOnMission && !lastIsOnMission && handledMission && fakePass) {
			description.append("?");
			handledMission = false;
			handledEverything = true;

			Disable();
		}

		lastIsOnMission = isOnMission;
	}
}
