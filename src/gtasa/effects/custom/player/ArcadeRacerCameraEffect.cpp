#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/MathHelper.h"

#include <CModelInfo.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class ArcadeRacerCameraEffect : public EffectBase
{
    bool wasInVehicle = false;

    static inline float rotation = 0.0f;

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

        // Debug print
        // Events::drawAfterFadeEvent += []
        // {
        //     gamefont::Print (gamefont::LeftBottom, gamefont::AlignLeft,
        //                      std::to_string (rotation).c_str
        //                      (), 20.0f, 60.0f, FONT_DEFAULT, 1.0f, 1.4f,
        //                      color::White, 2, color::Black, true);
        // };
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
            CColModel *colModel = vehicle->GetColModel ();
            float      diffBack = colModel->m_boundBox.m_vecMax.x
                             - colModel->m_boundBox.m_vecMin.x;
            float diffUp = colModel->m_boundBox.m_vecMax.z
                           - colModel->m_boundBox.m_vecMin.z;

            // TODO: Fix experimental "rotate with car" code
            if (false)
            {
                CMatrix *matrix = vehicle->GetMatrix ();
                rotation        = MathHelper::ToDegrees (
                                      atan2 (matrix->up.y - (M_PI / 2), matrix->up.z))
                           + 90.0f;
            }
            else
            {
                rotation = 0.0f;
            }

            Command<eScriptCommands::COMMAND_ATTACH_CAMERA_TO_VEHICLE> (
                vehicle, 0.0f, -diffBack - 4.0f, diffUp, 0.0f, 0.0f, 1.0f,
                rotation, 2);

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