#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

#include <CStreaming.h>

class WeaponRouletteEffect : public EffectBase
{
    int                                      wait          = 0;
    std::vector<std::pair<eWeaponType, int>> storedWeapons = {};
    std::vector<eWeaponType>                 weapons
        = {// Melee
           WEAPON_GOLFCLUB, WEAPON_NIGHTSTICK, WEAPON_KNIFE, WEAPON_BASEBALLBAT,
           WEAPON_SHOVEL, WEAPON_POOLCUE, WEAPON_KATANA, WEAPON_CHAINSAW,

           // Handguns
           WEAPON_PISTOL, WEAPON_PISTOL_SILENCED, WEAPON_DESERT_EAGLE,

           // Shotguns
           WEAPON_SHOTGUN, WEAPON_SAWNOFF, WEAPON_SPAS12,

           // Sub-Machine Guns
           WEAPON_MICRO_UZI, WEAPON_MP5, WEAPON_TEC9,

           // Assault Rifles
           WEAPON_AK47, WEAPON_M4,

           // Rifles
           WEAPON_COUNTRYRIFLE, WEAPON_SNIPERRIFLE,

           // Heavy Weapons
           WEAPON_RLAUNCHER, WEAPON_RLAUNCHER_HS, WEAPON_FTHROWER,
           WEAPON_MINIGUN,

           // Projectiles
           WEAPON_GRENADE, WEAPON_TEARGAS, WEAPON_MOLOTOV,
           WEAPON_SATCHEL_CHARGE,

           // Special
           WEAPON_SPRAYCAN, WEAPON_EXTINGUISHER};

public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        wait = 0;
        storedWeapons.clear ();

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        for (CWeapon weapon : player->m_aWeapons)
        {
            if (weapon.m_nTotalAmmo > 0)
            {
                storedWeapons.push_back (
                    std::make_pair (weapon.m_nType, weapon.m_nTotalAmmo));
            }
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        player->GetPadFromPlayer ()->bDisablePlayerCycleWeapon = false;

        GameUtil::ClearWeaponsExceptParachute (player);

        for (auto const &[type, ammo] : storedWeapons)
        {
            int model = CWeaponInfo::GetWeaponInfo (type, 1)->m_nModelId1;
            CStreaming::RequestModel (model, 2);
            CStreaming::LoadAllRequestedModels (false);

            player->GiveWeapon (type, ammo, true);

            CStreaming::SetModelIsDeletable (model);
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        player->GetPadFromPlayer ()->bDisablePlayerCycleWeapon = true;

        GameUtil::ClearWeaponsExceptParachute (player);

        eWeaponType randomWeapon
            = weapons[inst->Random (0, (int) weapons.size () - 1)];

        int model = CWeaponInfo::GetWeaponInfo (randomWeapon, 1)->m_nModelId1;

        CStreaming::RequestModel (model, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (randomWeapon, 500, 1);
        player->SetCurrentWeapon (randomWeapon);

        CStreaming::SetModelIsDeletable (model);

        wait = inst->Random (1000, 5000);
    }
};

DEFINE_EFFECT (WeaponRouletteEffect, "effect_weapon_roulette", GROUP_WEAPONS);