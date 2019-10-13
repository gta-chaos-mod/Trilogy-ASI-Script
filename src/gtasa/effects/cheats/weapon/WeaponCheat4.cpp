#include "WeaponCheat4.h"

WeaponCheat4::WeaponCheat4()
	: EffectPlaceholder("cheat_weapons_4") {}

void WeaponCheat4::Enable() {
	EffectPlaceholder::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (!player) {
		return;
	}

	bool hasNightVision = player->DoWeHaveWeaponAvailable(WEAPON_NIGHTVISION);

	CStreaming::RequestModel(MODEL_MINIGUN, 2); // Minigun
	CStreaming::RequestModel(MODEL_GUN_DILDO2, 2); // Dildo 2
	CStreaming::RequestModel(hasNightVision ? MODEL_IRGOGGLES : MODEL_NVGOGGLES, 2); // Thermal Vision / Night Vision
	CStreaming::LoadAllRequestedModels(0);

	player->GiveWeapon(WEAPON_MINIGUN, 500, 1);
	player->GiveWeapon(WEAPON_DILDO2, 1, 1);
	player->GiveWeapon(hasNightVision ? WEAPON_INFRARED : WEAPON_NIGHTVISION, 1, 1);

	CStreaming::SetModelIsDeletable(MODEL_MINIGUN);
	CStreaming::SetModelIsDeletable(MODEL_GUN_DILDO2);
	CStreaming::SetModelIsDeletable(hasNightVision ? MODEL_IRGOGGLES : MODEL_NVGOGGLES);
}
