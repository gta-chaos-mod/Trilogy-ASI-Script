#include <effects/OneTimeEffect.h>

#include <extensions/ScriptCommands.h>

using namespace plugin;

class EveryoneLeavesAllVehiclesEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            Command<eScriptCommands::COMMAND_TASK_EVERYONE_LEAVE_CAR> (vehicle);
    }
};

DEFINE_EFFECT (EveryoneLeavesAllVehiclesEffect,
               "effect_everyone_leaves_all_vehicles", 0);