#pragma once

#include "util/EffectBase.h"

class MirroredWorldEffect : public EffectBase
{
    static RwRaster *   raster;
    static RwIm2DVertex vertices[4];

    static void ResetRaster ();

    static __int16 __fastcall HookedGetSteeringLeftRight (CPad *thisPad);
    static __int16 __fastcall HookedPedWalkLeftRight (CPad *thisPad);
    static __int16 __fastcall HookedGetPedWalkLeftRightAim (CPad *thisPad,
                                                            void *edx,
                                                            CPed *ped);
    static char __fastcall HookedPedLookLeft (CPad *thisPad);
    static char __fastcall HookedPedLookRight (CPad *thisPad);
    static void HookedRenderCrossHairsEmpty ();
    static void HookedDrawRadarEmpty ();
    static void __fastcall HookedCSprite2dDraw (CSprite2d *thisSprite,
                                                void *edx, CRect *rect,
                                                CRGBA *color);

public:
    MirroredWorldEffect ();

    void InitializeHooks () override;

    void Enable () override;
    void Disable () override;

    static void Render2dStuffEvent ();
};
