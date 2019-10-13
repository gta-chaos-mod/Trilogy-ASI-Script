#include "NoStaminaCheat.h"

NoStaminaCheat::NoStaminaCheat()
	: EffectPlaceholder("cheat_no_stamina") {}

void NoStaminaCheat::Enable() {
	EffectPlaceholder::Enable();

	CStats::SetStatValue(eStats::STAT_STAMINA, 0.0f); // Stamina
}
