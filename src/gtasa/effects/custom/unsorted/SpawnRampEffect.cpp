#include "util/EffectBase.h"

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class SpawnRampEffect : public EffectBase
{
    CObject *rampObject;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector position
            = player->TransformFromObjectSpace (CVector (0.0f, 10.0f, -0.1f));

        int model = 1634; // Ramp
        CStreaming::RequestModel (model, 2);
        CStreaming::LoadAllRequestedModels (false);
        Command<eScriptCommands::COMMAND_CREATE_OBJECT> (model, position.x,
                                                         position.y, position.z,
                                                         &rampObject);
        CStreaming::SetModelIsDeletable (model);

        CMatrix *matrix;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
            matrix = vehicle->GetMatrix ();
        else
            matrix = player->GetMatrix ();

        rampObject->SetMatrix (*matrix);
        rampObject->SetPosn (position);
        rampObject->m_nObjectType = OBJECT_MISSION2;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (rampObject && IsObjectPointerValid (rampObject))
            rampObject->Remove ();
    }
};

DEFINE_EFFECT (SpawnRampEffect, "effect_spawn_ramp", 0);