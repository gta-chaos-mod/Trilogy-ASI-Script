#include "QuakeFOVEffect.h"

QuakeFOVEffect::QuakeFOVEffect () : EffectBase ("effect_quake_fov")
{
    AddType ("camera");
}

void
QuakeFOVEffect::Enable ()
{
    EffectBase::Enable ();

    // Fix sky multitude
    static const float fSkyMultitudeFix = 10.0f;
    injector::WriteMemory<const void *> (0x714843, &fSkyMultitudeFix, true);
    injector::WriteMemory<const void *> (0x714860, &fSkyMultitudeFix, true);

    // Set vehicle max FOV
    static const float fVehMaxFov = *CDraw_pfScreenFieldOfView + 120.0f;
    injector::WriteMemory<const void *> (0x524BB4, &fVehMaxFov, true);
    injector::WriteMemory<float> (0x524BC5, *CDraw_pfScreenFieldOfView + 120.0f,
                                  true);

    // TODO: Fix crosshair position / Aiming point
    // Refer to ThirteenAG's widescreen fix perhaps?
    // https://github.com/ThirteenAG/WidescreenFixesPack/blob/master/source/GTASA.WidescreenFix/dllmain.cpp#L724
}

void
QuakeFOVEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    TheCamera.m_aCams[TheCamera.m_nActiveCam].m_fFOV = 120.0f;
}
