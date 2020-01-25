#include "MercedesSkinCheat.h"

MercedesSkinCheat::MercedesSkinCheat()
	: EffectPlaceholder("cheat_mercedes_skin") {}

void MercedesSkinCheat::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		Call<0x4AE8C0>("igmerc");
	}
}
