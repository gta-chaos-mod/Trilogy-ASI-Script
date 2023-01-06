// Effect created by gromcheck

#include "util/EffectBase.h"
#include "util/GenericUtil.h"

class SwimLikeTommyEffect : public EffectBase
{
    int wait = 0;

public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || !FindPlayerVehicle (-1, false)) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        bool cond = player->m_pIntelligence->GetTaskSwim ();
        cond |= player->m_nPhysicalFlags.bSubmergedInWater;

        pad->DisablePlayerControls = cond;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        bool cond = player->m_pIntelligence->GetTaskSwim ();
        cond |= player->m_nPhysicalFlags.bSubmergedInWater;

        if (cond)
        {
            player->m_fHealth -= player->m_fMaxHealth * 0.01f;
        }

        wait = 50;
    }
};

DEFINE_EFFECT (SwimLikeTommyEffect, "effect_swim_like_tommy",
               GROUP_HEALTH | GROUP_CONTROLS);