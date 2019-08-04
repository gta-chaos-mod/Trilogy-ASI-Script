#include "FailMission.h"

FailMission::FailMission(int _duration, std::string _description)
	: EffectPlaceholder(_duration, _description) {}

void FailMission::Enable() {
	Command<Commands::FAIL_CURRENT_MISSION>();

	if (*onMission) {
		Command<Commands::CLEAR_SMALL_PRINTS>();
		Command<Commands::PRINT_BIG_Q>("M_FAIL", 5000, 1);
	}
}
