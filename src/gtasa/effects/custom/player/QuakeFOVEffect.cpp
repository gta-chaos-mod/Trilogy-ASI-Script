#include "util/EffectBase.h"

#include <CCamera.h>
#include <CDraw.h>

class QuakeFOVEffect : public EffectBase
{
    static inline float fieldOfView = 150.0f;

    float *CDraw_pfScreenFieldOfView = (float *) 0x8D5038;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        // Fix sky multitude
        static float fSkyMultitudeFix = 10.0f;
        injector::WriteMemory<float *> (0x714841 + 2, &fSkyMultitudeFix, true);
        injector::WriteMemory<float *> (0x71485E + 2, &fSkyMultitudeFix, true);

        // // Set vehicle max FOV
        // static float fVehMaxFov = *CDraw_pfScreenFieldOfView + fieldOfView;
        // injector::WriteMemory<float *> (0x524BB2 + 2, &fVehMaxFov, true);
        // injector::WriteMemory<float> (0x524BC5, fVehMaxFov, true);

        // injector::WriteMemory<float *> (0x516E24 + 2, &fieldOfView, true);
        // injector::MakeNOP (0x52C976, 5u);

        // TODO: Fix crosshair position / Aiming point
        // Refer to ThirteenAG's widescreen fix perhaps?
        // https://github.com/ThirteenAG/WidescreenFixesPack/blob/master/source/GTASA.WidescreenFix/dllmain.cpp#L724
    }

    void
    OnTick (EffectInstance *inst) override
    {
        // TODO: Figure out a way to stop the flickering (Objects seem to not be
        // in a "render" list with high FOV)
        TheCamera.m_aCams[TheCamera.m_nActiveCam].m_fFOV = fieldOfView;
        CDraw::SetFOV (fieldOfView);
    }
};

DEFINE_EFFECT (QuakeFOVEffect, "effect_quake_fov", GROUP_CAMERA);