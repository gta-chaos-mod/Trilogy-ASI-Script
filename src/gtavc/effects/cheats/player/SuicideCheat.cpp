#include "SuicideCheat.h"

SuicideCheat::SuicideCheat()
	: EffectPlaceholder("cheat_suicide") {}

void SuicideCheat::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->InflictDamage(0, eWeaponType::WEAPONTYPE_UNARMED, FLT_MAX, (ePedPieceTypes)0, 0);
	}
}
