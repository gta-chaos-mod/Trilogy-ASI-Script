#include "util/EffectBase.h"

class TeleportAllNPCsToPlayerEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || player->m_nAreaCode) return false;

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped->IsPlayer ()) continue;

            if (ped && ped->m_fHealth > 0.0f) return true;
        }

        return true;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CanActivate ()) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector position = player->GetPosition ();

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped == player || ped->m_pVehicle) continue;

            ped->SetPosn (position
                          + CVector (inst->Random (-1.0f, 1.0f),
                                     inst->Random (-1.0f, 1.0f), 3.0f));
        }

        inst->Disable ();
    }
};

DEFINE_EFFECT (TeleportAllNPCsToPlayerEffect,
               "effect_teleport_all_npcs_to_player", 0);