#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CRadar.h>

class RadarZoomEffect : public EffectBase
{
    static inline float zoom = 250.0f;

    float instanceZoom = 250.0f;

public:
    RadarZoomEffect (float zoom = 250.0f)
    {
        this->instanceZoom = zoom;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        zoom = instanceZoom;

        HOOK (inst, Hooked_CRadar_DrawRadarMap, void (), 0x586D4E);
    }

    static void
    Hooked_CRadar_DrawRadarMap (auto &&cb)
    {
        CRadar::m_radarRange = zoom;

        cb ();
    }
};

// clang-format off
DEFINE_EFFECT (RadarZoomEffect, "effect_radar_zoom_small", GROUP_HUD, 100.0f);
DEFINE_EFFECT (RadarZoomEffect, "effect_radar_zoom_large", GROUP_HUD, 3000.0f);
// clang-format on