#include "util/EffectBase.h"

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

            float diffBack = colModel->m_boundBox.m_vecMax.x
                             - colModel->m_boundBox.m_vecMin.x;
            float diffUp = colModel->m_boundBox.m_vecMax.z
                           - colModel->m_boundBox.m_vecMin.z;
            Command<eScriptCommands::COMMAND_ATTACH_CAMERA_TO_VEHICLE> (
                vehicle, 0.0f, -diffBack - 4.0f, diffUp, 0.0f, 0.0f, 1.0f, 0.0f,
                2);

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