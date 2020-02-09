#include "DisableRadarBlipsEffect.h"

DisableRadarBlipsEffect::DisableRadarBlipsEffect ()
    : EffectBase ("effect_disable_radar_blips")
{
    AddType ("hud");
}

void
DisableRadarBlipsEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    HookJump (0x58AA2D, HookedBlipsDraw);
    HookCall (0x575B44, HookedBlipsDraw);
}

void
DisableRadarBlipsEffect::HookedBlipsDraw ()
{
}
