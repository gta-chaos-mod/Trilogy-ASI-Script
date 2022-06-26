// To fix flickering make sure the mod "OpenLimitAdjuster" is installed.

#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CCamera.h>
#include <CDraw.h>

template <float maxFieldOfView> class FOVEffect : public EffectBase
{
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
        inst->WriteMemory<float *> (0x714841 + 2, &fSkyMultitudeFix);
        inst->WriteMemory<float *> (0x71485E + 2, &fSkyMultitudeFix);
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

// clang-format off
using SuperLowFOVEffect = FOVEffect<10.0f>;
DEFINE_EFFECT (SuperLowFOVEffect, "effect_super_low_fov", GROUP_CAMERA);

using LowFOVEffect = FOVEffect<35.0f>;
DEFINE_EFFECT (LowFOVEffect, "effect_low_fov", GROUP_CAMERA);

using QuakeFOVEffect = FOVEffect<120.0f>;
DEFINE_EFFECT (QuakeFOVEffect, "effect_quake_fov", GROUP_CAMERA);
// clang-format on