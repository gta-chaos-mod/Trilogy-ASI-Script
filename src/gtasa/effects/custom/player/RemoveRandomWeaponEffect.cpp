#include "effects/OneTimeEffect.h"

#include <CWeaponInfo.h>

class RemoveRandomWeaponEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return GetPossibleWeapons ().size () > 0;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        std::vector<CWeapon> possibleWeapons = GetPossibleWeapons ();
        if (possibleWeapons.size () == 0) return;

        int random = inst->Random (0, (int) possibleWeapons.size () - 1);

        player->ClearWeapon (possibleWeapons[random].m_eWeaponType);
    }

    std::vector<CWeapon>
    GetPossibleWeapons ()
    {
        std::vector<CWeapon> possibleWeapons = {};

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return possibleWeapons;

        for (int i = 1; i < 13; i++)
        {
            CWeapon weapon = player->m_aWeapons[i];
            if (weapon.m_nAmmoTotal > 0) possibleWeapons.push_back (weapon);
        }

        return possibleWeapons;
    }
};

DEFINE_EFFECT (RemoveRandomWeaponEffect, "effect_remove_random_weapon", 0);