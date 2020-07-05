#pragma once

#include <utility>

#include "util/EffectBase.h"

#include "util/ColorHelper.h"

#include "CModelInfo.h"
#include "CVehicleModelInfo.h"

class PrideCarsEffect : public EffectBase
{
private:
    static float                                  hueShift;
    static std::list<std::pair<RwRGBA *, RwRGBA>> resetMaterialColors;

public:
    PrideCarsEffect ();

    void Enable () override;
    void Disable () override;

    void HandleTick () override;

private:
    static void SetupRenderEvent (CVehicle *vehicle);
    static void ResetAfterRenderEvent (CVehicle *vehicle);
    static void ModifyCarPaint (CVehicle *vehicle);

    static RpMaterial *MaterialCallback (RpMaterial *material, void *color);
    static RpAtomic *  AtomicCallback (RpAtomic *atomic, void *color);
};
