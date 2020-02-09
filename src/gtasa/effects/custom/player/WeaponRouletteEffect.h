#pragma once

#include "util/EffectBase.h"

#include "CStreaming.h"

#include "util/GameUtil.h"
#include "util/RandomHelper.h"

class WeaponRouletteEffect : public EffectBase
{
private:
    int                      wait = 0;
    std::vector<eWeaponType> weapons
        = {// Melee
           eWeaponType::WEAPON_GOLFCLUB, eWeaponType::WEAPON_NIGHTSTICK,
           eWeaponType::WEAPON_KNIFE, eWeaponType::WEAPON_BASEBALLBAT,
           eWeaponType::WEAPON_SHOVEL, eWeaponType::WEAPON_POOLCUE,
           eWeaponType::WEAPON_KATANA, eWeaponType::WEAPON_CHAINSAW,

           // Handguns
           eWeaponType::WEAPON_PISTOL, eWeaponType::WEAPON_PISTOL_SILENCED,
           eWeaponType::WEAPON_DESERT_EAGLE,

           // Shotguns
           eWeaponType::WEAPON_SHOTGUN, eWeaponType::WEAPON_SAWNOFF,
           eWeaponType::WEAPON_SPAS12,

           // Sub-Machine Guns
           eWeaponType::WEAPON_MICRO_UZI, eWeaponType::WEAPON_MP5,
           eWeaponType::WEAPON_TEC9,

           // Assault Rifles
           eWeaponType::WEAPON_AK47, eWeaponType::WEAPON_M4,

           // Rifles
           eWeaponType::WEAPON_COUNTRYRIFLE, eWeaponType::WEAPON_SNIPERRIFLE,

           // Heavy Weapons
           eWeaponType::WEAPON_RLAUNCHER, eWeaponType::WEAPON_RLAUNCHER_HS,
           eWeaponType::WEAPON_FTHROWER, eWeaponType::WEAPON_MINIGUN,

           // Projectiles
           eWeaponType::WEAPON_GRENADE, eWeaponType::WEAPON_TEARGAS,
           eWeaponType::WEAPON_MOLOTOV, eWeaponType::WEAPON_SATCHEL_CHARGE,

           // Special
           eWeaponType::WEAPON_SPRAYCAN, eWeaponType::WEAPON_EXTINGUISHER};
    std::vector<std::pair<eWeaponType, int>> storedWeapons = {};

public:
    WeaponRouletteEffect ();

    void Enable () override;
    void Disable () override;

    void HandleTick () override;
};
