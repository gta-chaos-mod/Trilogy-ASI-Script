// Copyright (c) 2019 Lordmau5
#include "FailMission.h"

FailMission::FailMission(int _duration, const std::string& _description)
	: EffectPlaceholder(_duration, _description) {}

void FailMission::Enable() {
	if (CTheScripts::IsPlayerOnAMission()) {
		Command<Commands::CLEAR_SMALL_PRINTS>();
		Command<Commands::PRINT_BIG_Q>("M_FAIL", 5000, 1);
	}

	Command<Commands::FAIL_CURRENT_MISSION>();

	CGangWars::EndGangWar(false);
}
