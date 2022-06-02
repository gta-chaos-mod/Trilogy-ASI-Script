#include "util/DrawHelper.h"
#include "util/EffectBase.h"

#include <deque>

#include <CScene.h>

using namespace plugin;

// TODO: Refactor to `Delayed Controls`
// Keep copies of the NewState and set it to an empty one or the first one in
// the buffer
class DelayedScreenEffect : public EffectBase
{
    static inline CdeclEvent<AddressList<0x53EBF5, H_CALL>, PRIORITY_BEFORE,
                             ArgPickN<RwCamera *, 0>, RwCamera *(RwCamera *)>
        endUpdateEvent;
    static inline CdeclEvent<AddressList<0x745C7D, H_CALL>, PRIORITY_BEFORE,
                             ArgPickNone, void ()>
        createCameraSubRasterEvent;

    static inline RwIm2DVertex vertices[4];

    struct FrameData
    {
        RwRaster *raster;
    };

    static inline std::deque<FrameData> bufferedFrameData      = {};
    static const inline float           FRAME_DELAY_MULTIPLIER = 0.5f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        bufferedFrameData.clear ();

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
        for (FrameData data : bufferedFrameData)
            RwRasterDestroy (data.raster);

        bufferedFrameData.clear ();

        auto cameraRaster = Scene.m_pRwCamera->frameBuffer;

        // Reset raster and vertices
        DrawHelper::Append (vertices, 0, CVector2D (0, 0), plugin::color::White,
                            0, 0);
        DrawHelper::Append (vertices, 1,
                            CVector2D ((float) cameraRaster->width, 0),
                            plugin::color::White, 1, 0);
        DrawHelper::Append (vertices, 3,
                            CVector2D ((float) cameraRaster->width,
                                       (float) cameraRaster->height),
                            plugin::color::White, 1, 1);
        DrawHelper::Append (vertices, 2,
                            CVector2D (0, (float) cameraRaster->height),
                            plugin::color::White, 0, 1);
    }

    static int
    GetFrameDelay ()
    {
        // TODO: Get frame delay based on current framerate, not the frame limit
        return std::min (10,
                         (int) (RsGlobal.frameLimit * FRAME_DELAY_MULTIPLIER));
    }

    static void
    AddToBuffer (RwCamera *camera)
    {
        auto cameraRaster = camera->frameBuffer;

        FrameData data ({.raster = RwRasterCreate (cameraRaster->width,
                                                   cameraRaster->height,
                                                   cameraRaster->depth,
                                                   rwRASTERTYPECAMERATEXTURE)});

        RwRasterPushContext (data.raster);
        RwRasterRenderFast (camera->frameBuffer, 0, 0);
        RwRasterPopContext ();

        bufferedFrameData.push_back (data);
        if (bufferedFrameData.size () > GetFrameDelay ())
        {
            FrameData data = bufferedFrameData.front ();
            RwRasterDestroy (data.raster);

            bufferedFrameData.pop_front ();
        }
    }

    static void
    EndUpdateEvent (RwCamera *camera)
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        SetRenderState (rwRENDERSTATESHADEMODE, rwSHADEMODEFLAT);

        RwCameraEndUpdate (camera);
        AddToBuffer (camera);
        RwCameraBeginUpdate (camera);

        FrameData firstFrame = bufferedFrameData.front ();

        SetRenderState (rwRENDERSTATETEXTURERASTER, (int) firstFrame.raster);
        RwIm2DRenderPrimitive (rwPRIMTYPETRISTRIP, vertices, 4);
    }
};

DEFINE_EFFECT (DelayedScreenEffect, "effect_delayed_screen", GROUP_SCREEN);