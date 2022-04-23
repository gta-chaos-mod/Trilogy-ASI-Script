#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class RingRingEffect : public EffectBase
{
    int wait = 0;

public:
    bool
    CanActivate () override
    {
        return FindPlayerPed ();
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            Command<eScriptCommands::COMMAND_TASK_USE_MOBILE_PHONE> (player,
                                                                     false);
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CTask *phoneTask
                = player->m_pIntelligence->m_TaskMgr.FindTaskByType (3, 1600);
            if (!phoneTask)
            {
                CStreaming::RequestModel (330, 2);
                CStreaming::LoadAllRequestedModels (0);

                CStreaming::SetModelIsDeletable (330);

                Command<eScriptCommands::COMMAND_TASK_USE_MOBILE_PHONE> (
                    FindPlayerPed (), true);
                wait = 1000;
            }
        }
    }
};

DEFINE_EFFECT (RingRingEffect, "effect_ring_ring", 0);