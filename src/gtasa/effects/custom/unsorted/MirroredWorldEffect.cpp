#include "util/DrawHelper.h"
#include "util/EffectBase.h"
#include "util/Globals.h"
#include "util/hooks/HookMacros.h"

#include <CCamera.h>
#include <CDraw.h>
#include <CHud.h>
#include <CRadar.h>
#include <CScene.h>

using namespace plugin;

class MirroredWorldEffect : public EffectBase
{
    static inline CdeclEvent<AddressList<0x53EB12, H_CALL>, PRIORITY_BEFORE,
                             ArgPickNone, void ()>
        render2dStuffEvent;
    static inline CdeclEvent<AddressList<0x745C7D, H_CALL>, PRIORITY_BEFORE,
                             ArgPickNone, void ()>
        createCameraSubRasterEvent;

    static inline RwRaster    *raster      = nullptr;
    static inline RwIm2DVertex vertices[4] = {};

    static inline bool isWidescreenFixInstalled = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        isWidescreenFixInstalled
            = injector::ReadMemory<uint32_t> (0x5834BA + 2) != 0x859520;

        ResetRaster ();

        render2dStuffEvent += Render2dStuffEvent;
        createCameraSubRasterEvent += ResetRaster;

        HOOK_METHOD_ARGS (inst, Hooked_CSprite2d_Draw,
                          void (CSprite2d *, CRect *, CRGBA *), 0x5860F7);

        // CHud::DrawCrossHairs
        HOOK (inst, Hooked_Empty, void (), 0x58FBBF);

        // CHud::DrawRadar
        HOOK (inst, Hooked_Empty, void (), 0x58FC53);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        render2dStuffEvent -= Render2dStuffEvent;
        createCameraSubRasterEvent -= ResetRaster;
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                pad->NewState.LeftStickX *= -1;
                // pad->NewState.LeftStickY *= -1;
                pad->NewState.RightStickX *= -1;
                // pad->NewState.RightStickY *= -1;

                pad->NewMouseControllerState.X *= -1;
                // pad->NewMouseControllerState.Y *= -1;

                // std::swap (pad->NewState.DPadUp, pad->NewState.DPadDown);
                // std::swap (pad->NewState.DPadLeft, pad->NewState.DPadRight);
            }
        }
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
                            1, 0);
        DrawHelper::Append (vertices, 1,
                            CVector2D ((float) cameraRaster->width, 0),
                            plugin::color::White, 0, 0);
        DrawHelper::Append (vertices, 3,
                            CVector2D ((float) cameraRaster->width,
                                       (float) cameraRaster->height),
                            plugin::color::White, 0, 1);
        DrawHelper::Append (vertices, 2,
                            CVector2D (0, (float) cameraRaster->height),
                            plugin::color::White, 1, 1);
    }

    static void
    Render2dStuffEvent ()
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        /* Render Radar */

        SetRenderState (rwRENDERSTATEZTESTENABLE, 0);
        SetRenderState (rwRENDERSTATEZWRITEENABLE, 0);
        SetRenderState (rwRENDERSTATEVERTEXALPHAENABLE, 1u);
        SetRenderState (rwRENDERSTATESRCBLEND, 5u);
        SetRenderState (rwRENDERSTATEDESTBLEND, 6u);
        SetRenderState (rwRENDERSTATEFOGENABLE, 0);
        SetRenderState (rwRENDERSTATECULLMODE, 1u);

        SetRenderState (rwRENDERSTATETEXTUREFILTER, 1u);
        SetRenderState (rwRENDERSTATEVERTEXALPHAENABLE, 0);
        SetRenderState (rwRENDERSTATEFOGENABLE, 0);
        SetRenderState (rwRENDERSTATESRCBLEND, 5u);
        SetRenderState (rwRENDERSTATEDESTBLEND, 6u);
        SetRenderState (rwRENDERSTATEVERTEXALPHAENABLE, 1u);
        SetRenderState (rwRENDERSTATETEXTUREFILTER, 2u);
        SetRenderState (rwRENDERSTATETEXTUREADDRESS, 3u);
        SetRenderState (rwRENDERSTATETEXTURERASTER, 0);
        SetRenderState (rwRENDERSTATESHADEMODE, 1u);
        SetRenderState (rwRENDERSTATEALPHATESTFUNCTION, 5u);
        SetRenderState (rwRENDERSTATEALPHATESTFUNCTIONREF, 0);

        if (!Globals::isDisableHUDEffectEnabled)
        {
            if (!TheCamera.m_bWideScreenOn) CHud::DrawCrossHairs ();

            if (!CHud::bScriptDontDisplayRadar && !TheCamera.m_bWideScreenOn)
            {
                CPlayerPed *player = FindPlayerPed ();
                CPad       *pad    = player->GetPadFromPlayer ();
                if ((!pad || !pad->GetDisplayVitalStats (player))
                    || FindPlayerVehicle (-1, false))
                {
                    // Calculate radar offset
                    float radarWidth = injector::ReadMemory<float> (0x866B78);
                    float oldX       = injector::ReadMemory<float> (0x858A10);

                    float calculation = isWidescreenFixInstalled
                                            ? (546.0f * CDraw::ms_fAspectRatio)
                                            : 640.0f;

                    float offset = calculation - radarWidth - 40;

                    injector::WriteMemory<float> (0x858A10, offset);
                    CHud::DrawRadar ();
                    injector::WriteMemory<float> (0x858A10, oldX);
                }
            }
        }

        Call<0x700CC0> (); // CPostEffects::ImmediateModeRenderStatesStore();
        Call<0x700D70> (); // CPostEffects::ImmediateModeRenderStatesSet

        SetRenderState (rwRENDERSTATESHADEMODE, rwSHADEMODEFLAT);

        RwCameraEndUpdate (Scene.m_pRwCamera);
        RwRasterPushContext (raster);
        RwRasterRenderFast (Scene.m_pRwCamera->frameBuffer, 0, 0);
        RwRasterPopContext ();
        RwCameraBeginUpdate (Scene.m_pRwCamera);

        SetRenderState (rwRENDERSTATETEXTURERASTER, (int) raster);

        RwIm2DRenderPrimitive (rwPRIMTYPETRISTRIP, vertices, 4);

        Call<0x700E00> (); // CPostEffects::ImmediateModeRenderStatesReStore
    }

    static void
    Hooked_CSprite2d_Draw (auto &&cb, CSprite2d *thisSprite, CRect *rect,
                           CRGBA *color)
    {
        std::swap (rect->left, rect->right);

        cb ();
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (MirroredWorldEffect, "effect_mirrored_world",
               GROUP_MIRRORED | GROUP_CONTROLS);