#include "util/EffectBase.h"
#include <extensions/ScriptCommands.h>

using namespace plugin;

class DisablePayNSprayEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("modlast", 0);
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("mds1SFS", 0);
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("bodLAwN", 0);
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("mdsSFSe", 0);
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("vEcmod", 0);

        Command<eScriptCommands::COMMAND_SET_NO_RESPRAYS> (true);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("modlast", 36);
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("mds1SFS", 37);
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("bodLAwN", 38);
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("mdsSFSe", 38);
        Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> ("vEcmod", 38);

        Command<eScriptCommands::COMMAND_SET_NO_RESPRAYS> (false);
    }
};

DEFINE_EFFECT (DisablePayNSprayEffect, "effect_disable_pay_n_spray",
               GROUP_VEHICLE_COLOR);
