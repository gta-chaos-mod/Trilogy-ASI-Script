#include "DisableBlipsMarkersPickupsEffect.h"

DisableBlipsMarkersPickupsEffect::DisableBlipsMarkersPickupsEffect ()
    : EffectBase ("effect_disable_blips_markers_pickups")
{
    AddType ("hud");
}

void
DisableBlipsMarkersPickupsEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    HookJump (0x58AA2D, HookedCRadarDrawBlips);
    HookCall (0x575B44, HookedCRadarDrawBlips);

    HookCall (0x53E18E, HookedCCoronasRender);

    HookJump (0x59F1ED, HookedCEntityRender);

    HookCall (0x7250B1, HookedC3dMarkerRender);
    HookCall (0x72606F, HookedCCheckpointRender);
}

void
DisableBlipsMarkersPickupsEffect::HookedCRadarDrawBlips ()
{
}

void
DisableBlipsMarkersPickupsEffect::HookedCCoronasRender ()
{
}

void
DisableBlipsMarkersPickupsEffect::HookedCEntityRender (
    CEntity *thisEntity)
{
    if (!thisEntity || thisEntity->m_nType == eEntityType::ENTITY_TYPE_OBJECT && static_cast<CObject*>(thisEntity)->m_nObjectType == 5)
    {
        // Rendern't
        return;
    }

    CallMethod<0x534310, CEntity *> (thisEntity);
}

void
DisableBlipsMarkersPickupsEffect::HookedC3dMarkerRender ()
{
}

void
DisableBlipsMarkersPickupsEffect::HookedCCheckpointRender ()
{
}