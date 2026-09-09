#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class RemoveAllWeaponsEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return HasAnyWeapon ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        GameUtil::ClearWeapons (player);
    }

    bool
    HasAnyWeapon ()
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return false;

        for (int i = 1; i < 13; i++)
        {
            CWeapon weapon = player->m_aWeapons[i];
            if (weapon.m_nAmmoTotal > 0) return true;
        }

        return false;
    }
};

DEFINE_EFFECT (RemoveAllWeaponsEffect, "effect_remove_all_weapons", 0);