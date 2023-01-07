// Effect created by gromcheck

#include "util/EffectBase.h"
#include "util/GenericUtil.h"

class SwimLikeTommyEffect : public EffectBase
{
    int wait = 0;

public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || FindPlayerVehicle (-1, false)) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        bool cond = player->m_pIntelligence->GetTaskSwim ();

        pad->DisablePlayerControls = cond;

        if (cond) DrainPlayerHealth (player);
    }

    void
    DrainPlayerHealth (CPlayerPed *player)
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        player->m_fHealth -= player->m_fMaxHealth * 0.01f;
        player->m_fHealth = std::max (0.0f, player->m_fHealth);

        wait = 50;
    }
};

DEFINE_EFFECT (SwimLikeTommyEffect, "effect_swim_like_tommy",
               GROUP_HEALTH | GROUP_CONTROLS);