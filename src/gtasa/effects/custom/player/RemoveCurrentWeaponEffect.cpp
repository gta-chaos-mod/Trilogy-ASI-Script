#include "effects/OneTimeEffect.h"

#include <CWeaponInfo.h>

class RemoveCurrentWeaponEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return false;

        return player->m_nSelectedWepSlot != 0;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        // Don't remove fists
        if (player->m_nSelectedWepSlot == 0) return;

        CWeapon weapon = player->m_aWeapons[player->m_nSelectedWepSlot];
        player->ClearWeapon (weapon.m_eWeaponType);
    }
};

DEFINE_EFFECT (RemoveCurrentWeaponEffect, "effect_remove_current_weapon", 0);