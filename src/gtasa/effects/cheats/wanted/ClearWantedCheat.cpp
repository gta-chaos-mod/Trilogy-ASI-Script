#include "ClearWantedCheat.h"

ClearWantedCheat::ClearWantedCheat()
	: EffectPlaceholder("cheat_clear_wanted")
{
	AddType("wanted");
}

void ClearWantedCheat::Enable() {
	EffectPlaceholder::Enable();

	CWanted* wanted = FindPlayerWanted(-1);
	if (wanted) {
		wanted->CheatWantedLevel(0);
	}
}
