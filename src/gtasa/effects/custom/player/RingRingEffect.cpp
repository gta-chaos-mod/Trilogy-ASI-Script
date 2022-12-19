#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CStreaming.h>
#include <eTaskType.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

// TODO: Prevent phone call in cutscenes or when player isn't safe?
// https://clips.twitch.tv/PlumpMoldyOilUnSane-hL7HE0ZU-D1R9XZR

// TODO: Can still softlock missions such as Just Business when it happens right
// before the player hops on the bike and the cutscene starts. Once the cutscene
// is over and the player regains control, the camera will be stuck.

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
        if (!player) return;

        Command<eScriptCommands::COMMAND_TASK_USE_MOBILE_PHONE> (player, false);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CTask *phoneTask = player->m_pIntelligence->m_TaskMgr.FindTaskByType (
            3, TASK_COMPLEX_USE_MOBILE_PHONE);
        if (phoneTask) return;

        if (!GameUtil::IsPlayerSafe ()) return;

        CStreaming::RequestModel (330, 2);
        CStreaming::LoadAllRequestedModels (false);

        CStreaming::SetModelIsDeletable (330);

        Command<eScriptCommands::COMMAND_TASK_USE_MOBILE_PHONE> (
            FindPlayerPed (), true);

        wait = 1000;
    }
};

DEFINE_EFFECT (RingRingEffect, "effect_ring_ring", 0);