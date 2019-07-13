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
	Weapon::Weapon(eWeaponType weaponType, int modelID, int ammo = 1);
};

class WeaponPack {
public:
	static WeaponPack* WeaponPack::Cheat1;
	static WeaponPack* WeaponPack::Cheat2;
	static WeaponPack* WeaponPack::Cheat3;
	static WeaponPack* WeaponPack::CheatParachute;

	std::list<Weapon*> weapons;

public:
	void WeaponPack::AddWeapon(Weapon* weapon);

	WeaponPack::WeaponPack(std::initializer_list<Weapon*> weapons);
};

class Weapons {
public:
	static void Weapons::Clear();
	static void Weapons::Give(WeaponPack* weaponPack);
	static void Weapons::GiveByID(int id);
};

