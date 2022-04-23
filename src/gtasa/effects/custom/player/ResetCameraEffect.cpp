#include <effects/OneTimeEffect.h>

#include <extensions/ScriptCommands.h>

using namespace plugin;

class ResetCameraEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();
    }
};

DEFINE_EFFECT (ResetCameraEffect, "effect_reset_camera", 0);