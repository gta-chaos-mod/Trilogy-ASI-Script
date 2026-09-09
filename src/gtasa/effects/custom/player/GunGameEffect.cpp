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
           WEAPONTYPE_PISTOL, WEAPONTYPE_PISTOL_SILENCED,
           WEAPONTYPE_DESERT_EAGLE,

           // Shotguns
           WEAPONTYPE_SHOTGUN, WEAPONTYPE_SAWNOFF, WEAPONTYPE_SPAS12,

           // Sub-Machine Guns
           WEAPONTYPE_MICRO_UZI, WEAPONTYPE_MP5, WEAPONTYPE_TEC9,

           // Assault Rifles
           WEAPONTYPE_AK47, WEAPONTYPE_M4,

           // Rifles
           WEAPONTYPE_COUNTRYRIFLE, WEAPONTYPE_SNIPERRIFLE};

    static inline eWeaponType activeWeapon = WEAPONTYPE_UNARMED;

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
        activeWeapon = WEAPONTYPE_UNARMED;

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

        // Give the player a complementary firearm for their troubles
        if (storedWeapons.size () == 0)
        {
            GivePlayerWeapon (WEAPONTYPE_PISTOL, 50, true);
            return;
        }

        for (auto const &[type, ammo] : storedWeapons)
        {
            GivePlayerWeapon (type, ammo);
        }

        player->SetCurrentWeapon (activeWeapon);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        instance = inst;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        if (!weaponsStored)
        {
            activeWeapon
                = player->m_aWeapons[player->m_nSelectedWepSlot].m_eWeaponType;

            for (CWeapon weapon : player->m_aWeapons)
            {
                if (weapon.m_nAmmoTotal > 0)
                {
                    storedWeapons.push_back (
                        std::make_pair (weapon.m_eWeaponType,
                                        weapon.m_nAmmoTotal));
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
    GivePlayerWeapon (eWeaponType type, int ammo,
                      bool setAsCurrentWeapon = false)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        int model = CWeaponInfo::GetWeaponInfo (type, 1)->m_nModelId;
        CStreaming::RequestModel (model, 2);
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (type, ammo, true);

        if (setAsCurrentWeapon)
        {
            player->SetCurrentWeapon (type);
        }

        CStreaming::SetModelIsDeletable (model);
    }

    static void
    GivePlayerActiveWeapon ()
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CWeaponInfo *info = CWeaponInfo::GetWeaponInfo (activeWeapon, 1);
        if (player->m_nSelectedWepSlot != info->m_nSlot
            || player->m_aWeapons[player->m_nSelectedWepSlot].m_eWeaponType
                   != activeWeapon)
        {
            GivePlayerWeapon (activeWeapon, 99999, true);
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