#include "util/EffectBase.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class ThermalVisionEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        Command<Commands::SET_INFRARED_VISION> (false);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        Command<Commands::SET_INFRARED_VISION> (true);
    }
};

DEFINE_EFFECT (ThermalVisionEffect, "effect_thermal_vision", GROUP_VISION);