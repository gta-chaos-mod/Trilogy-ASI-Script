#include "WeaponRouletteEffect.h"

WeaponRouletteEffect::WeaponRouletteEffect()
	: EffectBase("effect_weapon_roulette")
{
	AddType("weapons");
}

void WeaponRouletteEffect::Enable() {
	EffectBase::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		for (CWeapon weapon : player->m_aWeapons) {
			if (weapon.m_nTotalAmmo > 0) {
				storedWeapons.push_back(std::make_pair(weapon.m_nType, weapon.m_nTotalAmmo));
			}
		}
	}
}

void WeaponRouletteEffect::Disable() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->GetPadFromPlayer()->bDisablePlayerCycleWeapon = false;

		GameUtil::ClearWeaponsExceptParachute(player);

		for (std::pair<eWeaponType, int> pair : storedWeapons) {
			int model = CWeaponInfo::GetWeaponInfo(pair.first, 1)->m_nModelId1;
			CStreaming::RequestModel(model, 2);
			CStreaming::LoadAllRequestedModels(0);

			player->GiveWeapon(pair.first, pair.second, true);

			CStreaming::SetModelIsDeletable(model);
		}
	}

	EffectBase::Disable();
}

void WeaponRouletteEffect::HandleTick() {
	EffectBase::HandleTick();

	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->GetPadFromPlayer()->bDisablePlayerCycleWeapon = true;

		GameUtil::ClearWeaponsExceptParachute(player);

		eWeaponType randomWeapon = weapons[RandomHelper::Random(0, weapons.size() - 1)];

		int model = CWeaponInfo::GetWeaponInfo(randomWeapon, 1)->m_nModelId1;

		CStreaming::RequestModel(model, 2);
		CStreaming::LoadAllRequestedModels(0);

		player->GiveWeapon(randomWeapon, 500, 1);
		player->SetCurrentWeapon(randomWeapon);

		CStreaming::SetModelIsDeletable(model);
	}

	wait = RandomHelper::Random(1000, 5000);
}
