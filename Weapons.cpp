#include "Weapons.h"

Weapon::Weapon(eWeaponType weaponType, int modelID, int ammo) {
	this->weaponType = weaponType;
	this->modelID = modelID;
	this->ammo = ammo;
};

void WeaponPack::AddWeapon(Weapon* weapon) {
	weapons.push_back(weapon);
}

WeaponPack* WeaponPack::Cheat1 = new WeaponPack({
	new Weapon(WEAPON_BRASSKNUCKLE, MODEL_BRASSKNUCKLE),
	new Weapon(WEAPON_BASEBALLBAT, MODEL_BAT),
	new Weapon(WEAPON_PISTOL, MODEL_COLT45, 100),
	new Weapon(WEAPON_SHOTGUN, MODEL_CHROMEGUN, 50),
	new Weapon(WEAPON_MICRO_UZI, MODEL_MICRO_UZI, 150),
	new Weapon(WEAPON_AK47, MODEL_AK47, 120),
	new Weapon(WEAPON_COUNTRYRIFLE, MODEL_CUNTGUN, 25),
	new Weapon(WEAPON_RLAUNCHER, MODEL_ROCKETLA, 200),
	new Weapon(WEAPON_MOLOTOV, MODEL_MOLOTOV, 10),
	new Weapon(WEAPON_SPRAYCAN, MODEL_SPRAYCAN, 200)
});
WeaponPack* WeaponPack::Cheat2 = new WeaponPack({
	new Weapon(WEAPON_KNIFE, MODEL_KNIFECUR),
	new Weapon(WEAPON_DESERT_EAGLE, MODEL_DESERT_EAGLE, 40),
	new Weapon(WEAPON_SAWNOFF, MODEL_SAWNOFF, 40),
	new Weapon(WEAPON_TEC9, MODEL_TEC9, 150),
	new Weapon(WEAPON_M4, MODEL_M4, 150),
	new Weapon(WEAPON_SNIPERRIFLE, MODEL_SNIPER, 21),
	new Weapon(WEAPON_FTHROWER, MODEL_FLAME, 500), // 10 Flamethrower "charges" are actually 1, so instead of 50 we give this 500.
	new Weapon(WEAPON_GRENADE, MODEL_GRENADE, 10),
	new Weapon(WEAPON_EXTINGUISHER, MODEL_FIRE_EX, 200)
});
WeaponPack* WeaponPack::Cheat3 = new WeaponPack({
	new Weapon(WEAPON_CHAINSAW, MODEL_CHNSAW),
	new Weapon(WEAPON_PISTOL_SILENCED, MODEL_SILENCED, 40),
	new Weapon(WEAPON_SPAS12, MODEL_SHOTGSPA, 30),
	new Weapon(WEAPON_MP5, MODEL_MP5LNG, 100),
	new Weapon(WEAPON_M4, MODEL_M4, 150),
	new Weapon(WEAPON_RLAUNCHER_HS, MODEL_HEATSEEK, 200),
	new Weapon(WEAPON_SATCHEL_CHARGE, MODEL_SATCHEL, 5)
});
WeaponPack* WeaponPack::CheatParachute = new WeaponPack({
	new Weapon(WEAPON_PARACHUTE, MODEL_PARACHUTE)
});

WeaponPack::WeaponPack(std::initializer_list<Weapon*> weapons) {
	for (Weapon* weapon : weapons) {
		this->AddWeapon(weapon);
	}
}

void Weapons::Clear() {
	CPed* player = FindPlayerPed();
	if (player) {
		player->ClearWeapons();
	}
}

void Weapons::Give(WeaponPack* weaponPack) {
	CPed* player = FindPlayerPed();
	if (player) {
		if (weaponPack->weapons.size() == 0) {
			return;
		}

		for (Weapon* weapon : weaponPack->weapons) {
			CStreaming::RequestModel(weapon->modelID, GAME_REQUIRED);
			CStreaming::LoadAllRequestedModels(false);

			player->GiveWeapon(weapon->weaponType, weapon->ammo, true);
			CStreaming::SetModelIsDeletable(weapon->modelID);
		}
	}
}

void Weapons::GiveByID(int id) {
	WeaponPack* weaponPack = nullptr;
	switch (id) {
		case 0: {
			weaponPack = WeaponPack::Cheat1;
			break;
		}
		case 1: {
			weaponPack = WeaponPack::Cheat2;
			break;
		}
		case 2: {
			weaponPack = WeaponPack::Cheat3;
			break;
		}
		case 3: {
			weaponPack = WeaponPack::CheatParachute;
			break;
		}
		default: {
			return;
		}
	}
	
	if (weaponPack == nullptr) {
		return;
	}
	Weapons::Give(weaponPack);
}
