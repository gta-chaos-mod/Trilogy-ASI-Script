#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class GetParachuteEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return false;

        if (player->m_aWeapons[player->GetWeaponSlot (WEAPON_PARACHUTE)]
                .m_eWeaponType
            == WEAPON_PARACHUTE)
            return false;

        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();

        CPlayerPed *player = FindPlayerPed ();
        if (!player || !CanActivate ()) return;

        GiveParachute (player);
    }

    void
    GiveParachute (CPed *ped)
    {
        CStreaming::RequestModel (MODEL_GUN_PARA, 2);
        CStreaming::LoadAllRequestedModels (false);

        ped->GiveWeapon (WEAPON_PARACHUTE, 0, 1);
        ped->SetCurrentWeapon (WEAPON_PARACHUTE);
    }
};

DEFINE_EFFECT (GetParachuteEffect, "effect_get_parachute", 0);