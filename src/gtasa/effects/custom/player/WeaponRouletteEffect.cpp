#include <util/EffectBase.h>
#include <util/GameUtil.h>
#include <util/GenericUtil.h>

#include "CStreaming.h"

class WeaponRouletteEffect : public EffectBase
{
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
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            for (CWeapon weapon : player->m_aWeapons)
            {
                if (weapon.m_nTotalAmmo > 0)
                {
                    storedWeapons.push_back (
                        std::make_pair (weapon.m_nType, weapon.m_nTotalAmmo));
                }
            }
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            player->GetPadFromPlayer ()->bDisablePlayerCycleWeapon = false;

            GameUtil::ClearWeaponsExceptParachute (player);

            for (auto const &[type, ammo] : storedWeapons)
            {
                int model = CWeaponInfo::GetWeaponInfo (type, 1)->m_nModelId1;
                CStreaming::RequestModel (model, 2);
                CStreaming::LoadAllRequestedModels (0);

                player->GiveWeapon (type, ammo, true);

                CStreaming::SetModelIsDeletable (model);
            }
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0)
        {
            return;
        }

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            player->GetPadFromPlayer ()->bDisablePlayerCycleWeapon = true;

            GameUtil::ClearWeaponsExceptParachute (player);

            eWeaponType randomWeapon
                = weapons[inst->Random (0, (int) weapons.size () - 1)];

            int model
                = CWeaponInfo::GetWeaponInfo (randomWeapon, 1)->m_nModelId1;

            CStreaming::RequestModel (model, 2);
            CStreaming::LoadAllRequestedModels (0);

            player->GiveWeapon (randomWeapon, 500, 1);
            player->SetCurrentWeapon (randomWeapon);

            CStreaming::SetModelIsDeletable (model);
        }

        wait = inst->Random (1000, 5000);
    }
};

DEFINE_EFFECT (WeaponRouletteEffect, "effect_weapon_roulette", GROUP_WEAPONS);