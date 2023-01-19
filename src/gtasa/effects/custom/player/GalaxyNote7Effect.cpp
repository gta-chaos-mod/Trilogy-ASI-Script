#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

#include <CCheat.h>
#include <eTaskType.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class GalaxyNote7Effect : public EffectBase
{
    int  wait         = 1000;
    bool pickedUpCall = false;

public:
    bool
    CanActivate () override
    {
        return FindPlayerPed ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        wait         = 1000;
        pickedUpCall = false;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        bool phoneRinging = GameUtil::GetGlobalVariable<bool> (15);

        for (auto i = CTheScripts::pActiveScripts; i; i = i->m_pNext)
        {
            if (i->m_bIsActive && !std::strcmp("BCESAR2", i->m_szName))
            {
                phoneRinging = true;
                break;
            }
        }

        if (phoneRinging
            || player->m_pIntelligence->m_TaskMgr.FindTaskByType (
                3, TASK_COMPLEX_USE_MOBILE_PHONE))
        {
            pickedUpCall = true;
        }

        if (!pickedUpCall) return;

        wait -= (int) GenericUtil::CalculateTick (CTimer::ms_fTimeScale);
        if (wait > 0) return;

        Command<eScriptCommands::COMMAND_CLEAR_CHAR_TASKS_IMMEDIATELY> (player);

        CVector position = player->GetPosition ();
        Command<eScriptCommands::COMMAND_ADD_EXPLOSION> (position.x, position.y,
                                                         position.z, 0);

        Command<eScriptCommands::COMMAND_SET_CHAR_HEALTH> (player, 0);

        inst->Disable ();
    }
};

DEFINE_EFFECT (GalaxyNote7Effect, "effect_galaxy_note_7", 0);