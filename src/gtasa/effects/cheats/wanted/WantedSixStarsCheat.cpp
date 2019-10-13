#include "WantedSixStarsCheat.h"

WantedSixStarsCheat::WantedSixStarsCheat()
	: EffectPlaceholder("cheat_wanted_six_stars")
{
	AddType("wanted");
}

void WantedSixStarsCheat::Enable() {
	EffectPlaceholder::Enable();

	CWanted* wanted = FindPlayerWanted(-1);
	if (wanted) {
		wanted->CheatWantedLevel(6);
	}
}
