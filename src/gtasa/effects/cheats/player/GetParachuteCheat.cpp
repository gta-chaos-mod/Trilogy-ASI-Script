#include "GetParachuteCheat.h"

GetParachuteCheat::GetParachuteCheat()
	: EffectPlaceholder("cheat_get_parachute") {}

void GetParachuteCheat::Enable() {
	EffectPlaceholder::Enable();

	CCheat::ParachuteCheat();
}
