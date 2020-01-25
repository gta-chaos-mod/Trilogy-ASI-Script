#include "KenSkinCheat.h"

KenSkinCheat::KenSkinCheat()
	: EffectPlaceholder("cheat_ken_skin") {}

void KenSkinCheat::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		Call<0x4AE8C0>("igken");
	}
}
