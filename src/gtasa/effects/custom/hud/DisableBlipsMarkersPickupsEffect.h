#pragma once

#include "util/EffectBase.h"

#include "CRadar.h"
#include "CPickups.h"

class DisableBlipsMarkersPickupsEffect : public EffectBase
{
public:
    DisableBlipsMarkersPickupsEffect ();

    void InitializeHooks () override;

private:
    static void HookedCRadarDrawBlips ();
    static void HookedCCoronasRender ();
    static void __fastcall HookedCEntityRender (CEntity *thisEntity);
    static void HookedC3dMarkerRender ();
    static void HookedCCheckpointRender ();
};
