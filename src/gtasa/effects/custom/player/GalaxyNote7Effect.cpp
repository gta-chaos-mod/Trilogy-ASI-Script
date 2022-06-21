#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

#include <CCheat.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class GalaxyNote7Effect : public EffectBase
{
    int wait = 1000;

public:
    bool
    CanActivate () override
    {
        return FindPlayerPed ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        wait = 1000;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        bool phoneRinging = GameUtil::GetGlobalVariable<bool> (15);

        if (phoneRinging)
        {
            wait -= (int) GenericUtil::CalculateTick (CTimer::ms_fTimeScale);
            if (wait > 0) return;

            Command<eScriptCommands::COMMAND_CLEAR_CHAR_TASKS_IMMEDIATELY> (
                player);

            CVector position = player->GetPosition ();
            Command<eScriptCommands::COMMAND_ADD_EXPLOSION> (position.x,
                                                             position.y,
                                                             position.z, 0);

            CCheat::SuicideCheat ();

            inst->Disable ();
        }
    }
};

DEFINE_EFFECT (GalaxyNote7Effect, "effect_galaxy_note_7", 0);