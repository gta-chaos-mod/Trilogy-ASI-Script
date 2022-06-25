#include "util/DrawHelper.h"
#include "util/EffectBase.h"

#include <CMenuManager.h>
#include <CScene.h>

using namespace plugin;

class UpsideDownScreenEffect : public EffectBase
{
    static inline CdeclEvent<AddressList<0x53EBF5, H_CALL>, PRIORITY_BEFORE,
                             ArgPickN<RwCamera *, 0>, RwCamera *(RwCamera *)>
        endUpdateEvent;
    static inline CdeclEvent<AddressList<0x745C7D, H_CALL>, PRIORITY_BEFORE,
                             ArgPickNone, void ()>
        createCameraSubRasterEvent;

    static inline RwRaster    *raster      = nullptr;
    static inline RwIm2DVertex vertices[4] = {};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        ResetRaster ();

        endUpdateEvent += EndUpdateEvent;
        createCameraSubRasterEvent += ResetRaster;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        endUpdateEvent -= EndUpdateEvent;
        createCameraSubRasterEvent -= ResetRaster;
    }

    static void
    ResetRaster ()
    {
        if (raster) RwRasterDestroy (raster);

        auto cameraRaster = Scene.m_pRwCamera->frameBuffer;
        raster
            = RwRasterCreate (cameraRaster->width, cameraRaster->height,
                              cameraRaster->depth, rwRASTERTYPECAMERATEXTURE);

        // Reset raster and vertices
        DrawHelper::Append (vertices, 0, CVector2D (0, 0), plugin::color::White,
                            0, 1);
        DrawHelper::Append (vertices, 1,
                            CVector2D ((float) cameraRaster->width, 0),
                            plugin::color::White, 1, 1);
        DrawHelper::Append (vertices, 3,
                            CVector2D ((float) cameraRaster->width,
                                       (float) cameraRaster->height),
                            plugin::color::White, 1, 0);
        DrawHelper::Append (vertices, 2,
                            CVector2D (0, (float) cameraRaster->height),
                            plugin::color::White, 0, 0);
    }

    static void
    EndUpdateEvent (RwCamera *camera)
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        SetRenderState (rwRENDERSTATESHADEMODE, rwSHADEMODEFLAT);

        RwCameraEndUpdate (camera);
        RwRasterPushContext (raster);
        RwRasterRenderFast (camera->frameBuffer, 0, 0);
        RwRasterPopContext ();
        RwCameraBeginUpdate (camera);

        SetRenderState (rwRENDERSTATETEXTURERASTER, (int) raster);

        RwIm2DRenderPrimitive (rwPRIMTYPETRISTRIP, vertices, 4);
    }
};

DEFINE_EFFECT (UpsideDownScreenEffect, "effect_upside_down_screen",
               GROUP_SCREEN);