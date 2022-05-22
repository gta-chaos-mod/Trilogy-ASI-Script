#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <CStreaming.h>

class FlowerPowerEffect : public EffectBase
{
    std::vector<std::pair<eWeaponType, int>> storedWeapons = {};

public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
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

        GameUtil::ClearWeaponsExceptParachute (player);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

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
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        for (int i = WEAPON_BRASSKNUCKLE; i < WEAPON_FLARE; i++)
        {
            eWeaponType type = static_cast<eWeaponType> (i);
            if (type == WEAPON_FLOWERS) continue;

            if (type != WEAPON_PARACHUTE) player->ClearWeapon (type);
        }

        GivePlayerFlowers (player);
    }

    void
    GivePlayerFlowers (CPed *ped)
    {
        if (ped->DoWeHaveWeaponAvailable (WEAPON_FLOWERS)) return;

        CStreaming::RequestModel (MODEL_FLOWERA, 2); // Flowers
        CStreaming::LoadAllRequestedModels (false);

        ped->GiveWeapon (WEAPON_FLOWERS, 500, 1);

        CStreaming::SetModelIsDeletable (MODEL_FLOWERA);

        ped->SetCurrentWeapon (WEAPON_FLOWERS);
    }
};

DEFINE_EFFECT (FlowerPowerEffect, "effect_flower_power", GROUP_WEAPONS);