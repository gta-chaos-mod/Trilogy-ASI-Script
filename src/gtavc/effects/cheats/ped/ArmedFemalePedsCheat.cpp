#include "ArmedFemalePedsCheat.h"

ArmedFemalePedsCheat::ArmedFemalePedsCheat()
	: EffectPlaceholder("cheat_armed_female_peds") {}

void ArmedFemalePedsCheat::Enable() {
	EffectPlaceholder::Enable();

	CStreaming::SetModelIsDeletable(95);
	CStreaming::SetModelIsDeletable(96);
	CStreaming::SetModelTxdIsDeletable(95);
	CStreaming::SetModelTxdIsDeletable(96);
	CStreaming::RemoveCurrentZonesModels();
	CGangs::SetGangPedModels(6, 17, 57);
	CGangs::SetGangWeapons(6, eWeaponType::WEAPONTYPE_M4, eWeaponType::WEAPONTYPE_M4);
}
