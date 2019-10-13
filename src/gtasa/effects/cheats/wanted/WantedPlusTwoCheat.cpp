#include "WantedPlusTwoCheat.h"

WantedPlusTwoCheat::WantedPlusTwoCheat()
	: EffectPlaceholder("cheat_wanted_plus_two")
{
	AddType("wanted");
}

void WantedPlusTwoCheat::Enable() {
	EffectPlaceholder::Enable();

	CWanted* wanted = FindPlayerWanted(-1);
	if (wanted) {
		int targetWanted = min(wanted->m_nWantedLevel + 2, 6);
		wanted->CheatWantedLevel(targetWanted);
	}
}
