#include "ReloadAutosaveEffect.h"

ReloadAutosaveEffect::ReloadAutosaveEffect ()
    : EffectPlaceholder ("effect_reload_autosave")
{
}

void
ReloadAutosaveEffect::Enable ()
{
    EffectPlaceholder::Enable ();

    GameUtil::LoadFromFile ("chaos_mod\\chaos_autosave.b");
}
