// To fix flickering make sure the mod "OpenLimitAdjuster" is installed.

#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CCamera.h>
#include <CDraw.h>

class QuakeFOVEffect : public EffectBase
{
    float maxFieldOfView = 120.0f;

    float fieldOfView     = 70.0f;
    float fieldOfViewZoom = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        fieldOfView     = 70.0f;
        fieldOfViewZoom = 0.0f;

        // Fix sky multitude
        static float fSkyMultitudeFix = 10.0f;
        injector::WriteMemory<float *> (0x714841 + 2, &fSkyMultitudeFix, true);
        injector::WriteMemory<float *> (0x71485E + 2, &fSkyMultitudeFix, true);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        fieldOfViewZoom += GenericUtil::CalculateTick (0.001f);
        fieldOfViewZoom = std::clamp (fieldOfViewZoom, 0.0f, 1.0f);

        fieldOfView
            = GenericUtil::EaseOutBack (fieldOfViewZoom, 70.0f, maxFieldOfView);

        TheCamera.m_aCams[TheCamera.m_nActiveCam].m_fFOV = fieldOfView;
        CDraw::SetFOV (fieldOfView);
    }
};

DEFINE_EFFECT (QuakeFOVEffect, "effect_quake_fov", GROUP_CAMERA);