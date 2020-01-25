#include "JezzSkinCheat.h"

JezzSkinCheat::JezzSkinCheat()
	: EffectPlaceholder("cheat_jezz_skin") {}

void JezzSkinCheat::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		Call<0x4AE8C0>("igjezz");
	}
}
