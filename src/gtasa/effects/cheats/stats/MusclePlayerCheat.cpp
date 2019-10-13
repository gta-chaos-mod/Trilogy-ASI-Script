#include "MusclePlayerCheat.h"

MusclePlayerCheat::MusclePlayerCheat()
	: EffectPlaceholder("cheat_muscle_player") {}

void MusclePlayerCheat::Enable() {
	EffectPlaceholder::Enable();

	CStats::SetStatValue(eStats::STAT_MUSCLE, 1000.0f);

	GameUtil::RebuildPlayer();
}
