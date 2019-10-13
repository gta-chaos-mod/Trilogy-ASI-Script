#include "SkinnyPlayerCheat.h"

SkinnyPlayerCheat::SkinnyPlayerCheat()
	: EffectPlaceholder("cheat_skinny_player") {}

void SkinnyPlayerCheat::Enable() {
	EffectPlaceholder::Enable();

	CStats::SetStatValue(eStats::STAT_FAT, 0.0f);
	CStats::SetStatValue(eStats::STAT_MUSCLE, 0.0f);

	GameUtil::RebuildPlayer();
}
