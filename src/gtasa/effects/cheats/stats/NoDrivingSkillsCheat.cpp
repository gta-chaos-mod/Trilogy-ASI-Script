#include "NoDrivingSkillsCheat.h"

NoDrivingSkillsCheat::NoDrivingSkillsCheat()
	: EffectPlaceholder("cheat_no_driving_skills") {}

void NoDrivingSkillsCheat::Enable() {
	EffectPlaceholder::Enable();

	CStats::SetStatValue(eStats::STAT_DRIVING_SKILL, 0.0f); // Driving
	CStats::SetStatValue(eStats::STAT_FLYING_SKILL, 0.0f); // Flying
	CStats::SetStatValue(eStats::STAT_BIKE_SKILL, 0.0f); // Bike
	CStats::SetStatValue(eStats::STAT_CYCLING_SKILL, 0.0f); // Cycling
}
