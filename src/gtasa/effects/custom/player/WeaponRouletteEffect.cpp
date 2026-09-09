#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

#include <CStreaming.h>

class WeaponRouletteEffect : public EffectBase
{
    int                                      wait          = 0;
    std::vector<std::pair<eWeaponType, int>> storedWeapons = {};
    std::vector<eWeaponType>                 weapons       = {
        // Melee
        WEAPONTYPE_GOLFCLUB, WEAPONTYPE_NIGHTSTICK, WEAPONTYPE_KNIFE,
        WEAPONTYPE_BASEBALLBAT, WEAPONTYPE_SHOVEL, WEAPONTYPE_POOLCUE,
        WEAPONTYPE_KATANA, WEAPONTYPE_CHAINSAW,

        // Handguns
        WEAPONTYPE_PISTOL, WEAPONTYPE_PISTOL_SILENCED, WEAPONTYPE_DESERT_EAGLE,

        // Shotguns
        WEAPONTYPE_SHOTGUN, WEAPONTYPE_SAWNOFF, WEAPONTYPE_SPAS12,

        // Sub-Machine Guns
        WEAPONTYPE_MICRO_UZI, WEAPONTYPE_MP5, WEAPONTYPE_TEC9,

        // Assault Rifles
        WEAPONTYPE_AK47, WEAPONTYPE_M4,

        // Rifles
        WEAPONTYPE_COUNTRYRIFLE, WEAPONTYPE_SNIPERRIFLE,

        // Heavy Weapons
        WEAPONTYPE_RLAUNCHER, WEAPONTYPE_RLAUNCHER_HS, WEAPONTYPE_FTHROWER,
        WEAPONTYPE_MINIGUN,

        // Projectiles
        WEAPONTYPE_GRENADE, WEAPONTYPE_TEARGAS, WEAPONTYPE_MOLOTOV,
        WEAPONTYPE_SATCHEL_CHARGE,

        // Special
        WEAPONTYPE_SPRAYCAN, WEAPONTYPE_EXTINGUISHER
    };

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
            if (weapon.m_nAmmoTotal > 0)
            {
                storedWeapons.push_back (
                    std::make_pair (weapon.m_eWeaponType, weapon.m_nAmmoTotal));
            }
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        player->GetPadFromPlayer ()->bDisablePlayerCycleWeapon = false;

        GameUtil::ClearWeapons (player);

        for (auto const &[type, ammo] : storedWeapons)
        {
            int model = CWeaponInfo::GetWeaponInfo (type, 1)->m_nModelId;
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

        GameUtil::ClearWeapons (player);

        eWeaponType randomWeapon
            = weapons[inst->Random (0, (int) weapons.size () - 1)];

        int model = CWeaponInfo::GetWeaponInfo (randomWeapon, 1)->m_nModelId;

        CStreaming::RequestModel (model, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (randomWeapon, 500, 1);
        player->SetCurrentWeapon (randomWeapon);

        CStreaming::SetModelIsDeletable (model);

        wait = inst->Random (1000, 1000 * 5);
    }
};

DEFINE_EFFECT (WeaponRouletteEffect, "effect_weapon_roulette", GROUP_WEAPONS);