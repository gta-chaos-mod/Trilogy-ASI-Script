#include "effects/OneTimeEffect.h"

#include <CWeaponInfo.h>

class RemoveCurrentWeaponEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CWeapon weapon = player->m_aWeapons[player->m_nActiveWeaponSlot];
        player->ClearWeapon (weapon.m_nType);
    }
};

DEFINE_EFFECT (RemoveCurrentWeaponEffect, "effect_remove_current_weapon", 0);