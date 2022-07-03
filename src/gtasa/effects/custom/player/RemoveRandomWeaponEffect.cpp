#include "effects/OneTimeEffect.h"

#include <CWeaponInfo.h>

class RemoveRandomWeaponEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        std::vector<CWeapon> possibleWeapons = {};

        for (int i = 1; i < 13; i++)
        {
            CWeapon weapon = player->m_aWeapons[i];
            if (weapon.m_nTotalAmmo > 0) possibleWeapons.push_back (weapon);
        }

        if (possibleWeapons.size () == 0) return;

        int random = inst->Random (0, (int) possibleWeapons.size ());

        player->ClearWeapon (possibleWeapons[random].m_nType);
    }
};

DEFINE_EFFECT (RemoveRandomWeaponEffect, "effect_remove_random_weapon", 0);