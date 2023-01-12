#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/MathHelper.h"
#include "util/hooks/HookMacros.h"

#include <CModelInfo.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class ArcadeRacerCameraEffect : public EffectBase
{
    bool wasInVehicle = false;

public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false) != nullptr;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        wasInVehicle = false;

        HOOK_METHOD (inst, Hooked_CCam__Process_AttachedCam, int (CCam *),
                     0x527BE5);
    }

    static int
    Hooked_CCam__Process_AttachedCam (auto &&cb)
    {
        if (!IsEntityPointerValid (TheCamera.m_pAttachedEntity)) return 0;

        return cb ();
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (wasInVehicle)
            Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            CMatrix *cam = &TheCamera.m_mCameraMatrix;

            CColModel *colModel = vehicle->GetColModel ();
            float      diffBack = colModel->m_boundBox.m_vecMax.x
                             - colModel->m_boundBox.m_vecMin.x;
            float diffUp = colModel->m_boundBox.m_vecMax.z
                           - colModel->m_boundBox.m_vecMin.z;

            Command<eScriptCommands::COMMAND_ATTACH_CAMERA_TO_VEHICLE> (
                vehicle, 0.0f, -diffBack - 4.0f, diffUp * 1.25f, 0.0f, 0.0f,
                1.0f, 0.0f, 2);

            // Thanks to zolika for the rotation code <3
            CMatrix *matrix = vehicle->GetMatrix ();
            cam->right      = matrix->right;
            cam->up         = matrix->up;
            cam->at         = matrix->at;

            cam->right.x *= -1;
            cam->right.y *= -1;
            cam->right.z *= -1;

            CMatrix shakeMatrix;
            shakeMatrix.pos = {0, 0, 0};
            shakeMatrix.SetRotate (MathHelper::ToRadians (-15), 0, 0);

            auto tmpMat = *cam;
            auto mat    = tmpMat * shakeMatrix;
            cam->right  = mat.right;
            cam->up     = mat.up;
            cam->at     = mat.at;

            TheCamera.CopyCameraMatrixToRWCam (0);

            wasInVehicle = true;
        }
        else
        {
            if (wasInVehicle)
            {
                Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();

                wasInVehicle = false;
            }
        }
    }
};

DEFINE_EFFECT (ArcadeRacerCameraEffect, "effect_arcade_racer_camera", 0);