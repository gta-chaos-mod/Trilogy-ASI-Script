#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/hooks/HookMacros.h"

#include <CProjectileInfo.h>
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
        HOOK_METHOD_ARGS (inst, Hooked_CTaskSimpleFight__FightStrike,
                          void (void *, CPed *, CVector *), 0x629EED);

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

        GameUtil::ClearWeapons (player);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CWeaponInfo *info = CWeaponInfo::GetWeaponInfo (WEAPONTYPE_FLOWERS, 1);
        info->m_nFlags.b1stPerson = true;
        info->m_nNumCombos        = 14;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

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
        CWeaponInfo *info = CWeaponInfo::GetWeaponInfo (WEAPONTYPE_FLOWERS, 1);
        info->m_nFlags.b1stPerson = true;
        info->m_nNumCombos        = 0;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        for (int i = WEAPONTYPE_BRASSKNUCKLE; i < WEAPONTYPE_FLARE; i++)
        {
            eWeaponType type = static_cast<eWeaponType> (i);
            if (type == WEAPONTYPE_FLOWERS) continue;

            if (type != WEAPONTYPE_PARACHUTE) player->ClearWeapon (type);
        }

        GivePlayerFlowers (player);

        if (!TheCamera.Using1stPersonWeaponMode ()) return;

        if (player->m_nSelectedWepSlot != info->m_nSlot) return;

        CTheScripts::bDrawCrossHair = true;
    }

    void
    GivePlayerFlowers (CPed *ped)
    {
        if (ped->DoWeHaveWeaponAvailable (WEAPONTYPE_FLOWERS)) return;

        CStreaming::RequestModel (MODEL_FLOWERA, 2); // Flowers
        CStreaming::LoadAllRequestedModels (false);

        ped->GiveWeapon (WEAPONTYPE_FLOWERS, 500, 1);

        CStreaming::SetModelIsDeletable (MODEL_FLOWERA);

        ped->SetCurrentWeapon (WEAPONTYPE_FLOWERS);
    }

    static void
    SpawnRocket (CVector position)
    {
        CMatrix *matrix = TheCamera.m_matrix;
        CVector  direction (matrix->up.x, matrix->up.y, matrix->up.z);

        CProjectileInfo::AddProjectile (FindPlayerPed (), WEAPONTYPE_ROCKET,
                                        position, 1.0f, &direction, nullptr);
    }

    static void
    Hooked_CTaskSimpleFight__FightStrike (auto &&cb, void *task, CPed *ped,
                                          CVector *outPoint)
    {
        cb ();

        if (!ped->IsPlayer ()) return;

        if (!TheCamera.Using1stPersonWeaponMode ()) return;

        CWeaponInfo *flowerWeaponInfo
            = CWeaponInfo::GetWeaponInfo (WEAPONTYPE_FLOWERS, 1);

        if (ped->m_nSelectedWepSlot != flowerWeaponInfo->m_nSlot) return;

        CVector position
            = ped->TransformFromObjectSpace (CVector (0.0f, 5.0f, 0.5f));

        SpawnRocket (position);
    }
};

DEFINE_EFFECT (FlowerPowerEffect, "effect_flower_power", GROUP_WEAPONS);