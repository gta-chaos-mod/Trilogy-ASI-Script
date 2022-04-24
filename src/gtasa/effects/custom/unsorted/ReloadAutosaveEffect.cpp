#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

class ReloadAutosaveEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        GameUtil::LoadFromFile ("chaos_mod\\chaos_autosave.b");
    }
};

DEFINE_EFFECT (ReloadAutosaveEffect, "effect_reload_autosave", 0);