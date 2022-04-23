#include <util/EffectBase.h>

using namespace plugin;

class ForcedWalkEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::processScriptsEvent += OnProcessScripts;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::processScriptsEvent -= OnProcessScripts;

        CPlayerPed *player = FindPlayerPed ();
        if (player) player->m_pPlayerData->m_bPlayerSprintDisabled = false;
    }

    static void
    OnProcessScripts ()
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