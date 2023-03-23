#include "util/EffectBase.h"
#include <extensions/ScriptCommands.h>

using namespace plugin;

namespace
{
const std::pair<std::string, int> garages[]
    = {{"beacsv", 17},  {"blob6", 30},   {"blob69", 27},  {"blob7", 28},
       {"burbdo2", 26}, {"burbdoo", 29}, {"carlas1", 31}, {"CEsafe1", 32},
       {"cn2gar1", 24}, {"cn2gar2", 25}, {"dhangar", 45}, {"sav1sfe", 39},
       {"sav1sfw", 40}, {"svgsfs1", 42}, {"vEsvgrg", 18}, {"cjsafe", 16},
       {"LCKSfse", 41}};
}

class LockAllGaragesEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        for (const auto &garage : garages)
        {
            Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> (
                garage.first.data (), 0);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (const auto &garage : garages)
        {
            Command<eScriptCommands::COMMAND_CHANGE_GARAGE_TYPE> (
                garage.first.data (), garage.second);
        }
    }
};

DEFINE_EFFECT (LockAllGaragesEffect, "effect_lock_all_garages", 0);
