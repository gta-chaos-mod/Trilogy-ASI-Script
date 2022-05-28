// To fix flickering make sure the mod "OpenLimitAdjuster" is installed.

#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CCamera.h>
#include <CDraw.h>

class ZoomingFOVEffect : public EffectBase
{
    const float minFieldOfView = 50.0f;
    const float maxFieldOfView = 90.0f;

    float fieldOfViewZoom = 0.5f;
    bool  goingUp         = true;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        fieldOfViewZoom = 0.5f;
        goingUp         = true;

        // Fix sky multitude
        static float fSkyMultitudeFix = 10.0f;
        injector::WriteMemory<float *> (0x714841 + 2, &fSkyMultitudeFix, true);
        injector::WriteMemory<float *> (0x71485E + 2, &fSkyMultitudeFix, true);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        float adjustment = GenericUtil::CalculateTick (0.0005f);

        if (goingUp)
        {
            fieldOfViewZoom += adjustment;
            if (fieldOfViewZoom >= 1.0f) goingUp = false;
        }
        else
        {
            fieldOfViewZoom -= adjustment;
            if (fieldOfViewZoom <= 0.0f) goingUp = true;
        }

        fieldOfViewZoom = std::clamp (fieldOfViewZoom, 0.0f, 1.0f);
        float fieldOfView
            = GenericUtil::EaseInOutQubic (fieldOfViewZoom, minFieldOfView,
                                           maxFieldOfView);

        TheCamera.m_aCams[TheCamera.m_nActiveCam].m_fFOV = fieldOfView;
        CDraw::SetFOV (fieldOfView);
    }
};

DEFINE_EFFECT (ZoomingFOVEffect, "effect_zooming_fov", GROUP_CAMERA);