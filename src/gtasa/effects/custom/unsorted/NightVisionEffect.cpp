#include "util/EffectBase.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class NightVisionEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        Command<Commands::SET_NIGHT_VISION> (false);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        Command<Commands::SET_NIGHT_VISION> (true);
    }
};

DEFINE_EFFECT (NightVisionEffect, "effect_night_vision", GROUP_VISION);