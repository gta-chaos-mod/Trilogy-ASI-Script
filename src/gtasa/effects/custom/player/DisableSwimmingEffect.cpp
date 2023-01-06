// Effect created by gromcheck

#include "util/EffectBase.h"

class DisableSwimmingEffect : public EffectBase
{
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
};

DEFINE_EFFECT (DisableSwimmingEffect, "effect_disable_swimming",
               GROUP_CONTROLS);