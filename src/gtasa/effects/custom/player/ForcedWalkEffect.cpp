#include "util/EffectBase.h"

class ForcedWalkEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                pad->NewState.m_bPedWalk                       = true;
                player->m_pPlayerData->m_bPlayerSprintDisabled = true;
            }
        }
    }
};

DEFINE_EFFECT (ForcedWalkEffect, "effect_forced_walk", 0);