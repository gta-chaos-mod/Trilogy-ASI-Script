#include "WeaponCheat2.h"

WeaponCheat2::WeaponCheat2()
	: EffectPlaceholder("cheat_weapons_2") {}

void WeaponCheat2::Enable() {
	EffectPlaceholder::Enable();

	CCheat::WeaponCheat2();
}
