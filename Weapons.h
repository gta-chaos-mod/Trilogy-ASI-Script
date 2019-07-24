#pragma once

#include "plugin.h"
#include "common.h"

#include "CStreaming.h"

#include <algorithm>
#include <list>

class Weapon {
public:
	eWeaponType weaponType = eWeaponType::WEAPON_UNARMED;
	int modelID = 0;
	int ammo = 0;

public:
	Weapon(eWeaponType weaponType, int modelID, int ammo = 1);
};

class WeaponPack {
public:
	static WeaponPack* Cheat1;
	static WeaponPack* Cheat2;
	static WeaponPack* Cheat3;
	static WeaponPack* CheatParachute;

	std::list<Weapon*> weapons;

public:
	void AddWeapon(Weapon* weapon);

	WeaponPack(std::initializer_list<Weapon*> weapons);
};

class Weapons {
public:
	static void Clear();
	static void Give(WeaponPack* weaponPack);
	static void GiveByID(int id);
};

