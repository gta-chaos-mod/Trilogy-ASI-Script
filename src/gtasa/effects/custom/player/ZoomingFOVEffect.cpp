// To fix flickering make sure the mod "OpenLimitAdjuster" is installed.

#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CCamera.h>
#include <CDraw.h>

class ZoomingFOVEffect : public EffectBase
{
    const float minFieldOfView = 50.0f;
    const float maxFieldOfView = 90.0f;

    float fieldOfView = 70.0f;
    bool  goingUp     = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        fieldOfView = 70.0f;
        goingUp     = false;

        // Fix sky multitude
        static float fSkyMultitudeFix = 10.0f;
        injector::WriteMemory<float *> (0x714841 + 2, &fSkyMultitudeFix, true);
        injector::WriteMemory<float *> (0x71485E + 2, &fSkyMultitudeFix, true);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        float adjustment = GenericUtil::CalculateTick (0.05f);

        if (goingUp)
        {
            fieldOfView += adjustment;
            if (fieldOfView > maxFieldOfView) goingUp = false;
        }
        else
        {
            fieldOfView -= adjustment;
            if (fieldOfView < minFieldOfView) goingUp = true;
        }

        TheCamera.m_aCams[TheCamera.m_nActiveCam].m_fFOV = fieldOfView;
        CDraw::SetFOV (fieldOfView);
    }
};

DEFINE_EFFECT (ZoomingFOVEffect, "effect_zooming_fov", GROUP_CAMERA);