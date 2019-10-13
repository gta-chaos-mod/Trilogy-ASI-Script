#include "WeaponCheat3.h"

WeaponCheat3::WeaponCheat3()
	: EffectPlaceholder("cheat_weapons_3") {}

void WeaponCheat3::Enable() {
	EffectPlaceholder::Enable();

	CCheat::WeaponCheat3();
}
