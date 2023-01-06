#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

#include <CStreaming.h>

class GunGameEffect : public EffectBase
{
    int                                      wait          = 0;
    bool                                     weaponsStored = false;
    std::vector<std::pair<eWeaponType, int>> storedWeapons = {};

    static inline std::vector<eWeaponType> weapons
        = {// Handguns
           WEAPON_PISTOL, WEAPON_PISTOL_SILENCED, WEAPON_DESERT_EAGLE,

           // Shotguns
           WEAPON_SHOTGUN, WEAPON_SAWNOFF, WEAPON_SPAS12,

           // Sub-Machine Guns
           WEAPON_MICRO_UZI, WEAPON_MP5, WEAPON_TEC9,

           // Assault Rifles
           WEAPON_AK47, WEAPON_M4,

           // Rifles
           WEAPON_COUNTRYRIFLE, WEAPON_SNIPERRIFLE};

    static inline eWeaponType activeWeapon = WEAPON_UNARMED;

    static inline EffectInstance *instance = nullptr;

public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        wait          = 0;
        weaponsStored = false;
        storedWeapons.clear ();
        activeWeapon = WEAPON_UNARMED;

        HOOK_METHOD_ARGS (inst, Hooked_CPedDamageResponseCalculator_WillKillPed,
                          void (CPedDamageResponseCalculator *, CPed *, void *,
                                char),
                          0x4B5B27);
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
        instance = inst;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        if (!weaponsStored)
        {
            for (CWeapon weapon : player->m_aWeapons)
            {
                if (weapon.m_nTotalAmmo > 0)
                {
                    storedWeapons.push_back (
                        std::make_pair (weapon.m_eWeaponType,
                                        weapon.m_nTotalAmmo));
                }
            }

            weaponsStored = true;

            SelectRandomWeapon ();
        }

        player->GetPadFromPlayer ()->bDisablePlayerCycleWeapon = true;

        GivePlayerActiveWeapon ();

        wait = 1000;
    }

    static void
    GivePlayerActiveWeapon ()
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CWeaponInfo *info = CWeaponInfo::GetWeaponInfo (activeWeapon, 1);
        if (player->m_nActiveWeaponSlot != info->m_nSlot
            || player->m_aWeapons[player->m_nActiveWeaponSlot].m_eWeaponType
                   != activeWeapon)
        {
            int model = info->m_nModelId1;

            CStreaming::RequestModel (model, 2);
            CStreaming::LoadAllRequestedModels (false);

            player->GiveWeapon (activeWeapon, 9999, 1);
            player->SetCurrentWeapon (activeWeapon);

            CStreaming::SetModelIsDeletable (model);
        }
    }

    static void
    SelectRandomWeapon ()
    {
        eWeaponType randomWeapon
            = weapons[instance->Random (0, (int) weapons.size () - 1)];

        CWeaponInfo *randomInfo = CWeaponInfo::GetWeaponInfo (randomWeapon, 1);
        CWeaponInfo *activeInfo = CWeaponInfo::GetWeaponInfo (activeWeapon, 1);

        if (randomWeapon == activeWeapon
            || (randomInfo && activeInfo
                && randomInfo->m_nSlot == activeInfo->m_nSlot))
        {
            SelectRandomWeapon ();
            return;
        }

        activeWeapon = randomWeapon;
    }

    static void
    Hooked_CPedDamageResponseCalculator_WillKillPed (
        auto &&cb, CPedDamageResponseCalculator *thisCalc, CPed *ped, void *a3,
        char a4)
    {
        cb ();

        if (!ped || !thisCalc || !thisCalc->m_pDamager
            || thisCalc->m_weaponType != activeWeapon)
            return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        if (ped->m_fHealth <= 0.0f && thisCalc->m_pDamager == player)
        {
            SelectRandomWeapon ();
        }
    }
};

DEFINE_EFFECT (GunGameEffect, "effect_gun_game", GROUP_WEAPONS);