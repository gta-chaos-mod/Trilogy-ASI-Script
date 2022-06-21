#include "effects/OneTimeEffect.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class AddRandomBlipsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (int i = 0; i < inst->Random (5, 15); i++)
        {
            float x      = inst->Random (-3000.0f, 3000.0f);
            float y      = inst->Random (-3000.0f, 3000.0f);
            int   sprite = inst->Random (0, 63);

            Command<eScriptCommands::COMMAND_ADD_SPRITE_BLIP_FOR_COORD> (
                x, y, 0.0f, sprite);
        }
    }
};

DEFINE_EFFECT (AddRandomBlipsEffect, "effect_add_random_blips", 0);