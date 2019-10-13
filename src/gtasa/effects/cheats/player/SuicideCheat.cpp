#include "SuicideCheat.h"

SuicideCheat::SuicideCheat()
	: EffectPlaceholder("cheat_suicide") {}

void SuicideCheat::Enable() {
	EffectPlaceholder::Enable();

	CCheat::SuicideCheat();
}
