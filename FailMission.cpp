#include "FailMission.h"

FailMission::FailMission(int _duration, std::string _description)
	: EffectPlaceholder(_duration, _description) {}

void FailMission::Enable() {
	Command<Commands::FAIL_CURRENT_MISSION>();
}
